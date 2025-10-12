#include <iostream>
#include "../include/renderer.hpp"
#include "../include/visual-effects/visualEffect.hpp"
// MAP
#include "../include/map/entryZone.hpp"
#include "../include/map/exitZone.hpp"
#include "../include/map/coreStorage.hpp"
#include "../include/map/path.hpp"
#include "../include/map/openZone.hpp"
// TOWERS
#include "../include/towers/gatling.hpp"
#include "../include/towers/mortar.hpp"
#include "../include/towers/laser.hpp"

Renderer::Renderer(sf::RenderWindow& win, tgui::Gui& g)
    : window(win), gui(g), ctx(window, *this, tileSize, 0) {}

sf::Vector2i Renderer::screenToTile(int mouseX, int mouseY) const {
    float localX = (mouseX) / (tileSize);
    float localY = (mouseY) / (tileSize);
    return { static_cast<int>(localX), static_cast<int>(localY) };
}

const sf::Texture& Renderer::getTexture(const std::string& filename) {
    static std::unordered_map<std::string, sf::Texture> cache;
    if (cache.find(filename) == cache.end()) {
        sf::Texture tex;
        if (!tex.loadFromFile("../assets/" + filename)) {
            std::cerr << "[Renderer] Missing texture: " << filename << std::endl;
            if (!tex.loadFromFile("../assets/missing_texture.png"))
                std::cerr << "Failed to load missing_texture.png as fallback.\n";
        }
        tex.setSmooth(true);
        cache[filename] = std::move(tex);
    }
    return cache.at(filename);
}

void Renderer::computeScaling(const Game& game) {
    const Map& map = game.getMap();
    const int mapWidth = map.getWidth();
    const int mapHeight = map.getHeight();

    sf::Vector2u winSize = window.getSize();

    float scaleX = static_cast<float>(winSize.x) / (mapWidth * tileSize);
    float scaleY = static_cast<float>(winSize.y) / (mapHeight * tileSize);

    // Choisir le plus petit facteur pour garder les proportions (tiles carrées)
    scaleFactor = std::min(scaleX, scaleY);
    
    tileSize *= scaleFactor;
    ctx.tileSize = tileSize;
}

void Renderer::render(const Game& game) {
    ctx.tick = game.getTick();

    // Draw map
    game.getMap().render(ctx);
    highlightTile(game); // Highlight tiles

    // Draw creatures
    for (const auto& c : game.getCreatures())
        c->render(ctx);


    // Draw Towers
    for (const auto& t : game.getTowers())
        t->render(ctx);
        
    // Draw visual effects
    for (const auto& e : game.getVisualEffects())
        e->render(window, tileSize);

    // Draw HUD
    drawHUD(game);
}

void Renderer::highlightTile(const Game& game) {
    const Map& map = game.getMap();
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    sf::Vector2i tilePos = screenToTile(mouse.x, mouse.y);
    if (tilePos.x >= 0 && tilePos.x < map.getWidth() &&
        tilePos.y >= 0 && tilePos.y < map.getHeight()) {
        Tile* hover = map.getTile(tilePos.x, tilePos.y);
        if (dynamic_cast<OpenZone*>(hover)) {
            sf::RectangleShape highlight({tileSize, tileSize});
            highlight.setPosition({tilePos.x * tileSize, tilePos.y * tileSize});
            highlight.setFillColor(sf::Color(255, 255, 0, 80));
            window.draw(highlight);
        }
    }
}

void Renderer::drawHUD(const Game& game) {
    // Retrieve core information
    Cores cores = game.getCores();
    int safeCores = cores.getSafe();
    int stolenCores = cores.getStolen();
    int lostCores = cores.getLost();
    int maxCores = safeCores + stolenCores + lostCores;

    // Load font once
    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded) {
        if (!font.openFromFile("../assets/arial.ttf")) {
            std::cerr << "Error: cannot load font ../assets/arial.ttf" << std::endl;
            return;
        }
        fontLoaded = true;
    }

    // --- PANEL DIMENSIONS ---
    const float panelWidth = 220.f;
    const float panelHeight = 150.f;

    // --- RESPONSIVE CENTERING ---
    sf::Vector2u winSize = window.getSize();
    float panelX = (winSize.x - panelWidth) / 2.f;
    float panelY = 10.f; // always near top

    // Draw background panel
    sf::RectangleShape panel({panelWidth, panelHeight});
    panel.setFillColor(sf::Color(0, 0, 0, 150));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(80, 80, 80));
    panel.setPosition({panelX, panelY});
    window.draw(panel);

    // --- INTERNAL LAYOUT SETTINGS ---
    const float marginX = 10.f;
    const float marginY = 10.f;
    const float startX = panelX + marginX;
    const float startY = panelY + marginY;

    // --- MATERIALS DISPLAY ---
    std::array<int, 3> balance = game.getPlayer().getMaterials().getBalance();

    const float iconSize = 24.f;
    const float spacingY = 22.f;
    const float textOffsetX = 35.f;

    struct ResourceDisplay {
        std::string filename;
        int value;
        float yOffset;
    };

    std::array<ResourceDisplay, 3> displays = {{
        { "icon_gold.png",   balance[0], startY },
        { "icon_silver.png", balance[1], startY + spacingY },
        { "icon_copper.png", balance[2], startY + spacingY * 2 }
    }};

    for (auto& res : displays) {
        // Draw icon
        sf::Sprite icon(getTexture(res.filename));
        const auto& texSize = getTexture(res.filename).getSize();
        icon.setScale(sf::Vector2f(iconSize / static_cast<float>(texSize.x),
                                   iconSize / static_cast<float>(texSize.y)));
        icon.setPosition({startX, res.yOffset});
        window.draw(icon);

        // Draw value
        sf::Text valueText(font, std::to_string(res.value), 18);
        valueText.setFillColor(sf::Color::White);
        valueText.setPosition({startX + textOffsetX, res.yOffset - 2.f});
        window.draw(valueText);
    }

    // --- CORE DISPLAY AREA (no label) ---
    const float availableWidth = panelWidth - 2 * marginX;
    const float circleY = startY + spacingY * 4.2f;
    const float radius = 6.f;
    float spacing = 18.f;

    // Adjust spacing if cores are too many
    float requiredWidth = maxCores * spacing;
    if (requiredWidth > availableWidth) {
        spacing = availableWidth / static_cast<float>(maxCores);
        if (spacing < radius * 2.2f)
            spacing = radius * 2.2f; // avoid overlap
    }

    // Center cores inside the panel
    float totalWidth = maxCores * spacing;
    float circleStartX = startX + (availableWidth - totalWidth) / 2.f;

    // --- DRAW CORES WITH WRAPPING ---
    const float circleYStart = startY + spacingY * 4.2f;
    float x = startX;                    // current X position
    float y = circleYStart;              // current Y position
    float maxLineWidth = availableWidth; // max width inside the panel

    for (int i = 0; i < maxCores; ++i) {
        // Wrap to next line if necessary
        if (x + radius * 2 > startX + maxLineWidth) {
            x = startX;                   // reset X to left margin
            y += radius * 2 + 4.f;        // move Y down for new line
        }

        sf::CircleShape circle(radius);
        circle.setPosition({x, y});
        circle.setOutlineThickness(1.f);
        circle.setOutlineColor(sf::Color(200, 200, 200));

        if (i < safeCores)
            circle.setFillColor(sf::Color(0, 150, 255));      // Blue = safe
        else if (i < safeCores + stolenCores)
            circle.setFillColor(sf::Color(255, 140, 0));      // Orange = stolen
        else
            circle.setFillColor(sf::Color(200, 50, 50));      // Red = lost

        window.draw(circle);

        x += spacing; // move to next X position
    }

}

void Renderer::handleMouseClick(int mouseX, int mouseY, Game& game) {
    sf::Vector2i tilePos = screenToTile(mouseX, mouseY);
    if (tilePos.x < 0 || tilePos.x >= game.getMap().getWidth() ||
        tilePos.y < 0 || tilePos.y >= game.getMap().getHeight())
        return;

    Tile* clicked = game.getMap().getTile(tilePos.x, tilePos.y);
    if (dynamic_cast<OpenZone*>(clicked)) {
        openTowerMenu(tilePos, game);
    }
}

void Renderer::openTowerMenu(sf::Vector2i tilePos, Game& game) {
    gui.removeAllWidgets();

    towerMenu = tgui::Panel::create({"200", "180"});
    towerMenu->setPosition({"50%", "50%"});
    towerMenu->getRenderer()->setBackgroundColor({40, 40, 40, 230});

    std::shared_ptr<tgui::Label> label = tgui::Label::create("Select a tower");
    label->setPosition(10, 10);
    towerMenu->add(label);

    auto addButton = [&](const std::string& name,
                         auto factory,
                         float y) {
        std::shared_ptr<tgui::Button> btn = tgui::Button::create(name);
        btn->setSize({"180", "30"});
        btn->setPosition(10, y);

        btn->onPress([&, factory, tilePos]() {
            auto tower = factory(tilePos.x, tilePos.y);
            PlaceTowerResult result = game.placeTower(std::move(tower));

            switch (result) {
                case PlaceTowerResult::NotBuildable:
                    showError("Cannot build here!");
                    break;
                case PlaceTowerResult::NotAffordable:
                    showError("Not enough materials!");
                    break;
                case PlaceTowerResult::Occupied:
                    showError("This tile is occupied!");
                    break;
                case PlaceTowerResult::Success:
                    // TODO: could have visual effect of construction
                    break;
            }

            gui.remove(towerMenu);
        });

        towerMenu->add(btn);
    };

    addButton("Gatling (50 Cu)", [](int x, int y) { return std::make_unique<Gatling>(x, y); }, 40);
    addButton("Laser (10 Ag, 100 Cu)", [](int x, int y) { return std::make_unique<Laser>(x, y); }, 80);
    addButton("Mortar (75 Cu)", [](int x, int y) { return std::make_unique<Mortar>(x, y); }, 120);

    gui.add(towerMenu);
}

void Renderer::togglePauseMenu(bool isPaused, Game& game) {
    paused = isPaused;
    gui.removeAllWidgets();

    if (isPaused) {
        pausePanel = tgui::Panel::create({"300", "200"});
        pausePanel->setPosition({"center", "center"});
        pausePanel->getRenderer()->setBackgroundColor({0, 0, 0, 150});

        std::shared_ptr<tgui::Label> label = tgui::Label::create("Game Paused");
        label->setPosition({"center", "20"});
        pausePanel->add(label);

        std::shared_ptr<tgui::Button> resumeBtn = tgui::Button::create("Resume");
        resumeBtn->setSize({"200", "40"});
        resumeBtn->setPosition({"center", "120"});
        resumeBtn->onPress([this]() {
            paused = false;
            gui.removeAllWidgets();
        });
        pausePanel->add(resumeBtn);

        gui.add(pausePanel);
    }
}

void Renderer::showError(const std::string& message) {
    std::shared_ptr<tgui::Panel> panel = tgui::Panel::create({"60%", "10%"});
    panel->setPosition({"20%", "5%"});  // Center horizontally
    panel->getRenderer()->setBackgroundColor({200, 50, 50, 230});
    panel->getRenderer()->setBorderColor({255, 255, 255});
    panel->getRenderer()->setBorders(2);

    std::shared_ptr<tgui::Label> label = tgui::Label::create(message);
    label->setPosition({"10", "5"});
    label->getRenderer()->setTextColor(tgui::Color::White);
    label->setTextSize(18);
    panel->add(label);

    gui.add(panel, "errorPanel");

    // Delete message after 2.5s
    std::shared_ptr<tgui::Timer> timer = tgui::Timer::create([panel, this]() {
        gui.remove(panel);
    }, std::chrono::milliseconds(2500));

}
