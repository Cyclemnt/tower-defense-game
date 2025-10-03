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

Renderer::Renderer(int width, int height, int tileSize)
    : window(sf::VideoMode({ static_cast<unsigned int>(width * tileSize), static_cast<unsigned int>(height * tileSize)}),
    "Tower Defense"), gui(window), tileSize(tileSize) {

    loadTextures();
}

void Renderer::loadTextures() {
    auto load = [](sf::Texture& tex, const std::string& path) {
        if (!tex.loadFromFile(path)) {
            std::cerr << "Erreur: impossible de charger la texture " << path << std::endl;
        }
    };

    load(texPath, "../assets/tile_path.png");
    load(texEmpty, "../assets/tile_empty.png");
    load(texOpen, "../assets/tile_open.png");
    load(texEntry, "../assets/tile_entry.png");
    load(texExit, "../assets/tile_exit.png");
    load(texCore, "../assets/tile_core_storage.png");
    load(texTowerGatling, "../assets/tower_gatling.png");
    load(texTowerMortar, "../assets/tower_mortar.png");
    load(texTowerLaser, "../assets/tower_laser.png");

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 4; ++j) {

            std::ostringstream oss ; 
            oss << "../assets/creature_" << ((i == 0) ? "minion_" : (i == 1) ? "drone_" : "tank_") << j << ".png";
            load(texCreature[i][j], oss.str());
        }
    }
}

bool Renderer::isOpen() const {
    return window.isOpen();
}

void Renderer::processEvents(Game& game) {
    while (auto eventOpt = window.pollEvent()) {
        const sf::Event& event = *eventOpt;

        // Verify if event is Closed
        if (event.is<sf::Event::Closed>()) {
            window.close();
        }

        // Manage other events if necessary
        gui.handleEvent(event);
    }
}

void Renderer::render(const Game& game) {
    window.clear(sf::Color::Black);

    drawMap(game);
    drawTowers(game);
    drawCreatures(game);
    drawUI(game);

    gui.draw();
    window.display();
}

void Renderer::drawMap(const Game& game) {
    for (int y = 0; y < game.getMap().getHeight(); y++) {
        for (int x = 0; x < game.getMap().getWidth(); x++) {
            Tile* tile = game.getMap().getTile(x, y);
            const sf::Texture* texture = &texNull;

            if (dynamic_cast<Path*>(tile)) texture = &texPath;
            else if (dynamic_cast<EmptyZone*>(tile)) texture = &texEmpty;
            else if (dynamic_cast<OpenZone*>(tile)) texture = &texOpen;
            else if (dynamic_cast<EntryZone*>(tile)) texture = &texEntry;
            else if (dynamic_cast<ExitZone*>(tile)) texture = &texExit;
            else if (dynamic_cast<CoreStorage*>(tile)) texture = &texCore;

            sf::Sprite sprite(*texture);
            sprite.setPosition({x * tileSize, y * tileSize});
            sprite.setScale({tileSize / float(texture->getSize().x),
                            tileSize / float(texture->getSize().y)});
            window.draw(sprite);
        }
    }
}

void Renderer::drawTowers(const Game& game) {
    for (auto& t : game.getTowers()) {
        const sf::Texture* texture = &texNull;

        if (dynamic_cast<Gatling*>(t.get())) texture = &texTowerGatling;
        else if (dynamic_cast<Mortar*>(t.get())) texture = &texTowerMortar;
        else if (dynamic_cast<Laser*>(t.get())) texture = &texTowerLaser;

        sf::Sprite sprite(*texture);
        sprite.setPosition({t->getX() * tileSize, t->getY() * tileSize});
        sprite.setScale({tileSize / float(texture->getSize().x),
                        tileSize / float(texture->getSize().y)});
        window.draw(sprite);
    }
}

void Renderer::drawCreatures(const Game& game) {
    for (auto& c : game.getCreatures()) {
        if (!c->isAlive()) continue;

        unsigned long tick = game.getTick();
        float animFramesPerSecond = c->getSpeed() * 2.0f; // 2.0f is the number of frame per tile
        int frameDurationTicks = (animFramesPerSecond > 0.0f) ? int(60 / animFramesPerSecond) : 1e9;

        int textureNumber = (tick / frameDurationTicks) % 4;

        const sf::Texture* texture = &texNull;

        if (dynamic_cast<Minion*>(c.get())) texture = &texCreature[0][textureNumber];
        else if (dynamic_cast<Drone*>(c.get())) texture = &texCreature[1][textureNumber];
        else if (dynamic_cast<Tank*>(c.get())) texture = &texCreature[2][textureNumber];

        sf::Sprite sprite(*texture);
        auto pos = c->getPosition();
        sprite.setPosition({pos[0] * tileSize, pos[1] * tileSize});
        sprite.setScale({tileSize / float(texture->getSize().x),
                        tileSize / float(texture->getSize().y)});
        window.draw(sprite);
    }
}

void Renderer::drawUI(const Game& game) {
}
