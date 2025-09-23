#include "../include/game.hpp"

#include <iostream>
#include <algorithm>

Game::Game(int w, int h, int initialCores)
    : map(w, h), pathfinder(map), cores(initialCores), materials(),
      tick(0) {
    // TODO: generate map
    // Map example :
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            map.placeTile(std::make_unique<Path>(i, j));
    map.placeTile(std::make_unique<EmptyZone>(1, 3));
    map.placeTile(std::make_unique<EmptyZone>(2, 3));
    map.placeTile(std::make_unique<EmptyZone>(3, 3));
    map.placeTile(std::make_unique<EmptyZone>(3, 2));
    map.placeTile(std::make_unique<EmptyZone>(3, 1));
    map.placeTile(std::make_unique<EmptyZone>(3, 0));
    // Interest points setup
    map.placeTile(std::make_unique<OpenZone>(2, 0));
    map.placeTile(std::make_unique<EntryZone>(0, 0));
    map.placeTile(std::make_unique<ExitZone>(4, 4));
    map.placeTile(std::make_unique<CoreStorage>(2, 2, 24));
}

void Game::spawnCreature(std::unique_ptr<Creature> creature) {
    // Assign path (Entry -> CoreStorage or Exit)
    if (!map.getEntries().empty() && !map.getExits().empty()) {
        Tile* start = map.getEntries()[0];
        Tile* goal = map.getExits()[0];

        auto path = pathfinder.findPath(start, goal);
        creature->setPath(path);
    }

    creatures.push_back(std::move(creature));
}

void Game::placeTower(std::unique_ptr<Tower> tower) {
    if (!map.getTile(tower.get()->getX(), tower.get()->getY())->isBuildable())
        throw std::runtime_error("Trying to place tower on non buildable tile");
    
    if (!player.canAfford(*tower))
        throw std::runtime_error("Player cannot afford a tower");
    player.pay(*tower);
    
    towers.push_back(std::move(tower));

    // TODO: update paths

}

void Game::update() {
    tick++;

    // Update creatures
    for (auto& c : creatures) {
        if (c->isAlive()) {
            c->update();
            // TODO: manage stealing/exiting
        }
    }

    // Update towers
    for (auto& t : towers) {
        t->update(reinterpret_cast<std::vector<Creature*>&>(creatures));
    }

    // Remove dead creatures
    creatures.erase(std::remove_if(creatures.begin(), creatures.end(),
                                   [](const std::unique_ptr<Creature>& c) { return !c->isAlive(); }),
                    creatures.end());
}

void Game::render() const {
    std::cout << "Tick: " << tick << "\n";
    //map.printMap();

    for (const auto& c : creatures) {
        if (c->isAlive()) {
            auto pos = c->getCurrentTile();
            if (pos) {
                std::cout << "Creature at (" << pos->getX() << "," << pos->getY()
                          << ") HP=" << c->getHealth()
                          << " Shield=" << c->getShield() << "\n";
            }
        }
    }
}

bool Game::isGameOver() const {
    return cores.getLost() > 0; // TODO: better condition
}
