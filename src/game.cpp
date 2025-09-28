#include "../include/game.hpp"

#include <iostream>
#include <algorithm>

Game::Game(int w, int h, int initialCores)
    : map(w, h), pathfinder(map), player(), cores(initialCores), tick(0) {
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
    map.placeTile(std::make_unique<ExitZone>(4, 3));
    map.placeTile(std::make_unique<CoreStorage>(2, 2, &cores));
    map.printMap();
}

const Map& Game::getMap() const { return map; }

const std::vector<std::unique_ptr<Creature>>& Game::getCreatures() const { return creatures; }

const std::vector<std::unique_ptr<Tower>>& Game::getTowers() const { return towers; }

void Game::spawnCreature(std::unique_ptr<Creature> creature) {
    if (map.getEntries().empty() || map.getCoreStorage() == nullptr || map.getExits().empty())
        throw std::runtime_error("Map missing entry or core storage or exit");
    // Assign path (Entry -> CoreStorage or Exit)
    Tile* start = map.getEntries()[0];
    Tile* goal = map.getCoreStorage();

    auto path = pathfinder.findPath(start, goal);
    if (path.empty()) path = pathfinder.findPath(start, goal, true);
    creature->setPath(path);

    creatures.push_back(std::move(creature));
}

PlaceTowerResult Game::placeTower(std::unique_ptr<Tower> tower) {
    Tile* tile = map.getTile(tower->getX(), tower->getY());

    if (!tile->isBuildable())
        return PlaceTowerResult::NotBuildable;

    if (!player.canAfford(*tower))
        return PlaceTowerResult::NotAffordable;

    player.pay(*tower);
    towers.push_back(std::move(tower));

    // Update every creature's path
    for (auto& c : creatures) {
        Tile* start = c->getCurrentTile();
        Tile* goal = c->getDestinationTile();
        auto newPath = pathfinder.findPath(start, goal);
        if (newPath.empty()) newPath = pathfinder.findPath(start, goal, true);
        c->setPath(newPath);
    }

    return PlaceTowerResult::Success;
}

void Game::update(float deltaTime) {
    tick++;

    // Update creatures
    for (auto& c : creatures) {
        if (c->isAlive()) {

            c->update(deltaTime);

            Tile* current = c->getCurrentTile();

            if (!c->isAlive())
                cores.returnCore(c->dropCores());
            
            // CoreStorage reached
            else if (auto storage = dynamic_cast<CoreStorage*>(current)) {
                if (c->getDestinationTile() == map.getCoreStorage()) {
                    // New path to exit
                    Tile* goal = map.getExits()[0];
                    auto newPath = pathfinder.findPath(current, goal);
                    c->setPath(newPath);
                }
            }

            // Exit reached
            else if (auto exit = dynamic_cast<ExitZone*>(current)) {
                if (c->getDestinationTile() == map.getExits()[0]) {
                    // TODO: make creature diseapear (and remove carried cores)
                    cores.loseCore(c->dropCores());
                }
            }
        }
    }

    // Update towers
    for (auto& t : towers) {
        t->update(deltaTime, creatures);
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
            auto pos = c->getPosition();
            std::cout << "Creature at (" << pos[0] << "," << pos[1]
                        << ") HP=" << c->getHealth()
                        << " Shield=" << c->getShield() << "\n";
        }
    }
}

bool Game::isGameOver() const {
    return cores.getLost() > 0; // TODO: better condition
}
