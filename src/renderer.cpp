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
    return sf::Vector2i(static_cast<int>(mouseX / tileSize),
                        static_cast<int>(mouseY / tileSize));
}

void Renderer::render(const Game& game) {
    const Map& map = game.getMap();

    // --- Draw map ---
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
            else if (dynamic_cast<CoreStorage*>(tile))
                tex = &getTexture("tile_core.png");
            else
                tex = &getTexture("tile_empty.png");

            sf::Sprite sprite(*tex);
            sprite.setPosition({static_cast<float>(x) * tileSize,
                                static_cast<float>(y) * tileSize});

            const auto& sz = tex->getSize();
            sprite.setScale(sf::Vector2f(tileSize / sz.x, tileSize / sz.y));
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

    // --- Creatures ---
    int frame = (game.getTick() / 8) % 4;
    for (const auto& c : game.getCreatures()) {
        std::string name = c->getTypeName();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        std::string filename = "creature_" + name + "_" + std::to_string(frame) + ".png";
        const sf::Texture& tex = getTexture(filename);
        sf::Sprite sprite(tex);
        sprite.setPosition({c->getPosition()[0] * tileSize,
                            c->getPosition()[1] * tileSize});
        const auto& sz = tex.getSize();
        sprite.setScale(sf::Vector2f(tileSize / sz.x, tileSize / sz.y));
        window.draw(sprite);
    }

    // --- Visual effects ---
    for (const auto& e : game.getVisualEffects())
        e->render(window, tileSize);

    // --- Towers ---
    for (const auto& t : game.getTowers()) {
        std::string name = t->getTypeName();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        std::string file = "tower_" + name + "_0.png";
        // TODO: change texture to change orientation
        const sf::Texture& tex = getTexture(file);
        sf::Sprite sprite(tex);
        sprite.setPosition({t->getX() * tileSize, t->getY() * tileSize});
        const auto& sz = tex.getSize();
        sprite.setScale(sf::Vector2f(tileSize / sz.x, tileSize / sz.y));
        window.draw(sprite);
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

    auto label = tgui::Label::create("Select a tower");
    label->setPosition(10, 10);
    towerMenu->add(label);

    auto addButton = [&](const std::string& name,
                         auto factory,
                         float y) {
        auto btn = tgui::Button::create(name);
        btn->setSize({"180", "30"});
        btn->setPosition(10, y);

        btn->onPress([&, factory, tilePos]() {
            auto tower = factory(tilePos.x, tilePos.y);
            auto result = game.placeTower(std::move(tower));

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

        auto label = tgui::Label::create("Game Paused");
        label->setPosition({"center", "20"});
        pausePanel->add(label);

        auto resumeBtn = tgui::Button::create("Resume");
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

void Renderer::showError(const std::string& message)
{
    auto panel = tgui::Panel::create({"60%", "10%"});
    panel->setPosition({"20%", "5%"});  // Center horizontally
    panel->getRenderer()->setBackgroundColor({200, 50, 50, 230});
    panel->getRenderer()->setBorderColor({255, 255, 255});
    panel->getRenderer()->setBorders(2);

    auto label = tgui::Label::create(message);
    label->setPosition({"10", "5"});
    label->getRenderer()->setTextColor(tgui::Color::White);
    label->setTextSize(18);
    panel->add(label);

    gui.add(panel, "errorPanel");

    // Draw right now
    //gui.draw();

    // Delete message after 2.5s
    std::shared_ptr<tgui::Timer> timer = tgui::Timer::create([panel, this]() {
        gui.remove(panel);
    }, std::chrono::milliseconds(2500));

}
