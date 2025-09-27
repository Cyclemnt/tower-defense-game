#include "../include/renderer.hpp"
#include "../include/map/entryZone.hpp"
#include "../include/map/exitZone.hpp"
#include "../include/map/coreStorage.hpp"
#include "../include/map/path.hpp"
#include "../include/map/openZone.hpp"

Renderer::Renderer(int width, int height, int tileSize)
    : window(sf::VideoMode(width * tileSize, height * tileSize), "Tower Defense"),
      gui(window), tileSize(tileSize) {

    loadTextures();

    // Exemple simple avec TGUI : bouton Quit
    auto quitButton = tgui::Button::create("Quit");
    quitButton->setPosition("5%", "5%");
    quitButton->setSize("10%", "5%");
    quitButton->onPress([&]{ window.close(); });
    gui.add(quitButton);
}

void Renderer::loadTextures() {
    texPath.loadFromFile("../assets/path.png");
    texEmpty.loadFromFile("../assets/empty.png");
    texOpen.loadFromFile("../assets/open.png");
    texEntry.loadFromFile("../assets/entry.png");
    texExit.loadFromFile("../assets/exit.png");
    texCore.loadFromFile("../assets/core.png");

    texTowerGatling.loadFromFile("../assets/tower_gatling.png");
    texTowerMortar.loadFromFile("../assets/tower_mortar.png");
    texTowerLaser.loadFromFile("../assets/tower_laser.png");

    texMinionCreature.loadFromFile("../assets/creature_minion.png");
    texDroneCreature.loadFromFile("../assets/creature_drone.png");
    texTankCreature.loadFromFile("../assets/creature_tank.png");

    
    texNull.loadFromFile("../assets/missing_texture.png");
}

bool Renderer::isOpen() const {
    return window.isOpen();
}

void Renderer::processEvents(Game& game) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
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
            sf::Sprite sprite;

            if (dynamic_cast<Path*>(tile)) sprite.setTexture(texPath);
            else if (dynamic_cast<EmptyZone*>(tile)) sprite.setTexture(texEmpty);
            else if (dynamic_cast<OpenZone*>(tile)) sprite.setTexture(texOpen);
            else if (dynamic_cast<EntryZone*>(tile)) sprite.setTexture(texEntry);
            else if (dynamic_cast<ExitZone*>(tile)) sprite.setTexture(texExit);
            else if (dynamic_cast<CoreStorage*>(tile)) sprite.setTexture(texCore);
            else sprite.setTexture(texNull);

            sprite.setPosition(x * tileSize, y * tileSize);
            sprite.setScale(tileSize / sprite.getTexture()->getSize().x,
                            tileSize / sprite.getTexture()->getSize().y);
            window.draw(sprite);
        }
    }
}

void Renderer::drawTowers(const Game& game) {
    for (auto& t : game.getTowers()) {
        sf::Sprite sprite;
        if (t->getTypeName() == "Gatling") sprite.setTexture(texTowerGatling);
        else if (t->getTypeName() == "Mortar") sprite.setTexture(texTowerMortar);
        else if (t->getTypeName() == "Laser") sprite.setTexture(texTowerLaser);
        else sprite.setTexture(texNull);

        sprite.setPosition(t->getX() * tileSize, t->getY() * tileSize);
        sprite.setScale(tileSize / sprite.getTexture()->getSize().x,
                        tileSize / sprite.getTexture()->getSize().y);
        window.draw(sprite);
    }
}

void Renderer::drawCreatures(const Game& game) {
    for (auto& c : game.getCreatures()) {
        if (!c->isAlive()) continue;

        sf::Sprite sprite;
        if (c->getTypeName() == "Minion") sprite.setTexture(texMinionCreature);
        else if (c->getTypeName() == "Drone") sprite.setTexture(texDroneCreature);
        else if (c->getTypeName() == "Tank") sprite.setTexture(texTankCreature);
        else sprite.setTexture(texNull);

        sprite.setPosition(c->getPosition()[0] * tileSize, c->getPosition()[1] * tileSize);
        sprite.setScale(tileSize / sprite.getTexture()->getSize().x,
                        tileSize / sprite.getTexture()->getSize().y);
        window.draw(sprite);
    }
}

void Renderer::drawUI(const Game& game) {
    // Exemple : afficher les cores et ressources
    // (tu peux utiliser TGUI Label ou SFML Text ici)
}
