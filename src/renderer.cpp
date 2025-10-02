#include "../include/renderer.hpp"
#include "../include/map/entryZone.hpp"
#include "../include/map/exitZone.hpp"
#include "../include/map/coreStorage.hpp"
#include "../include/map/path.hpp"
#include "../include/map/openZone.hpp"

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

    load(texPath, "../assets/path.png");
    load(texEmpty, "../assets/empty.png");
    load(texOpen, "../assets/open.png");
    load(texEntry, "../assets/entry.png");
    load(texExit, "../assets/exit.png");
    load(texCore, "../assets/core.png");
    load(texTowerGatling, "../assets/tower_gatling.png");
    load(texTowerMortar, "../assets/tower_mortar.png");
    load(texTowerLaser, "../assets/tower_laser.png");
    load(texMinionCreature, "../assets/creature_minion.png");
    load(texDroneCreature, "../assets/creature_drone.png");
    load(texTankCreature, "../assets/creature_tank.png");
    load(texNull, "../assets/missing_texture.png");
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

        if (t->getTypeName() == "Gatling") texture = &texTowerGatling;
        else if (t->getTypeName() == "Mortar") texture = &texTowerMortar;
        else if (t->getTypeName() == "Laser") texture = &texTowerLaser;

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

        const sf::Texture* texture = &texNull;

        if (c->getTypeName() == "Minion") texture = &texMinionCreature;
        else if (c->getTypeName() == "Drone") texture = &texDroneCreature;
        else if (c->getTypeName() == "Tank") texture = &texTankCreature;

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
