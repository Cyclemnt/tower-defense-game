#include "../include/renderer.hpp"
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
// CREATURES
#include "../include/creatures/minion.hpp"
#include "../include/creatures/drone.hpp"
#include "../include/creatures/tank.hpp"

#include <iostream>
#include <algorithm>

Renderer::Renderer(sf::RenderWindow& win, tgui::Gui& g)
    : window(win), gui(g) {}

sf::Texture& Renderer::getTexture(const std::string& filename) {
    if (textures.find(filename) == textures.end()) {
        sf::Texture tex;
        if (!tex.loadFromFile("../assets/" + filename)) {
            std::cerr << "[Renderer] Missing texture: " << filename << std::endl;
            if (!tex.loadFromFile("../assets/missing_texture.png"))
                std::cerr << "Failed to load missing_texture.png as fallback.\n";
        }
        tex.setSmooth(true);
        textures.insert({filename, std::move(tex)});
    }
    return textures.at(filename);
}

sf::Vector2i Renderer::screenToTile(int mouseX, int mouseY) const {
    float localX = (mouseX) / (tileSize);
    float localY = (mouseY) / (tileSize);
    return { static_cast<int>(localX), static_cast<int>(localY) };
}

uint32_t Renderer::pseudoRandomFromCoords(int x, int y) const {
    // Combine data with multiplication and bit shift
    uint32_t combined = (x * 73856093U) ^ (y * 19349663U);
    combined += emptyTileSeed & 0xFFFFFFFF; // Add seed

    return combined;
}

const sf::Texture& Renderer::getRandomEmptyTileTexture(int x, int y) {
    uint32_t rnd = pseudoRandomFromCoords(x, y) % 100;

    if (rnd < 70) return getTexture("tile_empty_1.png");
    else if (rnd < 90) return getTexture("tile_empty_1.png");
    else return getTexture("tile_empty_0.png");
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
}

void Renderer::render(const Game& game) {
    // --- Draw map ---
    drawMap(game);
    // --- Creatures ---
    drawCreatures(game);
    // --- Visual effects ---
    drawVisualEffects(game);
    // --- Towers ---
    drawTowers(game);
    // --- UI ---
    drawHUD(game);
}

void Renderer::drawMap(const Game& game) {
    const Map& map = game.getMap();
    for (int y = 0; y < map.getHeight(); ++y) {
        for (int x = 0; x < map.getWidth(); ++x) {
            Tile* tile = map.getTile(x, y);
            const sf::Texture* tex = nullptr;

            if (dynamic_cast<Path*>(tile))
                tex = &getTexture("tile_path.png");
            else if (dynamic_cast<OpenZone*>(tile))
                tex = &getTexture("tile_open.png");
            else if (dynamic_cast<EntryZone*>(tile))
                tex = &getTexture("tile_entry.png");
            else if (dynamic_cast<ExitZone*>(tile))
                tex = &getTexture("tile_exit.png");
            else if (CoreStorage* core = dynamic_cast<CoreStorage*>(tile)) {
                float ratio = 1.0f; // default value
                Cores cores = game.getCores();
                int safeCores = cores.getSafe();
                int maxCores = safeCores + cores.getStolen() + cores.getLost();
                if (maxCores > 0)
                    ratio = static_cast<float>(safeCores) / maxCores;

                if (ratio > 0.7f)
                    tex = &getTexture("tile_core_0.png");
                else if (ratio > 0.3f)
                    tex = &getTexture("tile_core_1.png");
                else
                    tex = &getTexture("tile_core_2.png");
            }
            else
                tex = &getRandomEmptyTileTexture(x, y);

            sf::Sprite sprite(*tex);
            sprite.setPosition({x * tileSize, y * tileSize});
            const sf::Vector2<unsigned int>& sz = tex->getSize();
            sprite.setScale({(tileSize / sz.x), (tileSize / sz.x)});
            window.draw(sprite);
        }
    }

    // --- Highlight tile under mouse ---
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

void Renderer::drawCreatures(const Game& game) {
    int frame = (game.getTick() / 8) % 4;
    for (const auto& c : game.getCreatures()) {
        std::string name = c->getTypeName();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        std::string filename = "creature_" + name + "_" + std::to_string(frame) + ".png";
        const sf::Texture& tex = getTexture(filename);
        sf::Sprite sprite(tex);
        sprite.setPosition({c->getPosition()[0] * tileSize, c->getPosition()[1] * tileSize});
        const sf::Vector2<unsigned int>& sz = tex.getSize();
        sprite.setScale({(tileSize / sz.x), (tileSize / sz.x)});
        window.draw(sprite);

        // --- Display Health and Shield ---
        float health = c->getHealth();
        float shield = c->getShield();
        float baseHealth = c->getBaseHealth();
        float baseShield = c->getBaseShield();

        float hpRatio = health / baseHealth;
        float shieldRatio = shield / baseShield;

        // Bar dimensions and positions
        float barWidth = tileSize * 0.5f;
        float barHeight = tileSize * 0.05f;
        float x = c->getPosition()[0] * tileSize + (tileSize - barWidth) * 0.5f;
        float baseY = c->getPosition()[1] * tileSize - barHeight - 4.0f;

        // Shield bar 
        if (baseShield > 0.0f) {
            float y = baseY - (barHeight + 2.0f); // above health bar

            // Background
            sf::RectangleShape backBar(sf::Vector2f(barWidth, barHeight));
            backBar.setFillColor(sf::Color(40, 40, 40));
            backBar.setPosition({x, y});
            window.draw(backBar);

            // Current shield
            sf::RectangleShape shieldBar(sf::Vector2f(barWidth * shieldRatio, barHeight));
            shieldBar.setFillColor(sf::Color(100, 150, 255, 200)); // light blue
            shieldBar.setPosition({x, y});
            window.draw(shieldBar);
        }
        // Health bar
        {
            float y = baseY;

            // Background
            sf::RectangleShape backBar(sf::Vector2f(barWidth, barHeight));
            backBar.setFillColor(sf::Color(40, 40, 40));
            backBar.setPosition({x, y});
            window.draw(backBar);

            // Color based on ratio
            sf::Color lifeColor(255 * (1 - hpRatio), 255 * hpRatio, 0);

            // Current health
            sf::RectangleShape hpBar(sf::Vector2f(barWidth * hpRatio, barHeight));
            hpBar.setFillColor(lifeColor);
            hpBar.setPosition({x, y});
            window.draw(hpBar);
        }
    }
}

void Renderer::drawVisualEffects(const Game& game) {
    for (const auto& e : game.getVisualEffects())
        e->render(window, tileSize);
}

void Renderer::drawTowers(const Game& game) {
    // TODO : define frame with target position
    for (const auto& t : game.getTowers()) {
        std::string name = t->getTypeName();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        std::string filename = "tower_" + name + "_0" + ".png";
        const sf::Texture& tex = getTexture(filename);
        sf::Sprite sprite(tex);
        sprite.setPosition({t->getX() * tileSize, t->getY() * tileSize});
        const sf::Vector2<unsigned int>& sz = tex.getSize();
        sprite.setScale(sf::Vector2f(tileSize / sz.x, tileSize / sz.x));
        window.draw(sprite);
    }
}


void Renderer::drawHUD(const Game& game) {
    // Load font for numbers
    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded) {
        if (!font.openFromFile("../assets/arial.ttf")) {
            std::cerr << "Error: cannot load font ../assets/arial.ttf" << std::endl;
            return;
        }
        fontLoaded = true;
    }

    // HUD background panel
    sf::RectangleShape panel;
    panel.setSize({150.f, 90.f});
    panel.setFillColor(sf::Color(0, 0, 0, 150));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(80, 80, 80));
    panel.setPosition({10.f, 10.f});
    window.draw(panel);

    // Get player resources 
    std::array<int, 3> balance = game.getPlayer().getMaterials().getBalance();

    // Display parameters 
    const float iconSize = 24.f;
    const float startX = 20.f;
    const float startY = 20.f;
    const float spacingY = 22.f;
    const float textOffsetX = 35.f;

    struct ResourceDisplay {
        std::string filename;
        int value;
        float yOffset;
    };

    // List of resources to display 
    std::array<ResourceDisplay, 3> displays = {{
        { "icon_gold.png",   balance[0], startY },
        { "icon_silver.png", balance[1], startY + spacingY },
        { "icon_copper.png", balance[2], startY + spacingY * 2 }
    }};

    // --- Draw resource icons and values ---
    for (auto& res : displays) {
        // Icon sprite
        sf::Sprite icon(getTexture(res.filename));
        icon.setPosition({startX, res.yOffset});
        const sf::Vector2<unsigned int>& size = getTexture(res.filename).getSize();
        icon.setScale(sf::Vector2f(iconSize / static_cast<float>(size.x),
                                   iconSize / static_cast<float>(size.y)));
        window.draw(icon);

        // Value text
        sf::Text valueText(font, std::to_string(res.value), 18);
        valueText.setFont(font);
        valueText.setString(std::to_string(res.value));
        valueText.setCharacterSize(18);
        valueText.setFillColor(sf::Color::White);
        valueText.setPosition({startX + textOffsetX, res.yOffset - 2.f});
        window.draw(valueText);
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
