#include "../include/game.hpp"
#include "../include/visual-effects/tracerEffect.hpp"
#include "../include/visual-effects/visualEffect.hpp"
#include "../include/towers/gatling.hpp"
#include <iostream>
#include <algorithm>
#include <memory>

Game::Game(int w, int h, int initialCores)
    : map(w, h), pathfinder(map), player(), cores(initialCores), tick(0) {
    // TODO: generate map
    // Map example :
    
    for (int i : {8, 9, 10}) {
        map.placeTile(std::make_unique<Path>(i, 0));
        map.placeTile(std::make_unique<Path>(i, 2));
    }
    map.placeTile(std::make_unique<EntryZone>(1, 0));
    map.placeTile(std::make_unique<ExitZone>(0, 1));
    for (int i = 1; i < 14; i++)
        if (i != 7) map.placeTile(std::make_unique<Path>(i, 1));
    map.placeTile(std::make_unique<CoreStorage>(9, 1, &cores));

    for (int i = 1; i < 8; i++)
        map.placeTile(std::make_unique<Path>(6, i));
    map.placeTile(std::make_unique<Path>(7, 7));
    for (int i = 7; i < 14; i++)
        map.placeTile(std::make_unique<Path>(i, 8));
    for (int i = 1; i < 9; i++)
        map.placeTile(std::make_unique<Path>(13, i));
    for (int i : {4, 5, 6}) {
        map.placeTile(std::make_unique<Path>(12, i));
        map.placeTile(std::make_unique<Path>(14, i));
    }
    map.placeTile(std::make_unique<OpenZone>(13, 5));
    for (int i : {0, 1}) {
        map.placeTile(std::make_unique<OpenZone>(5, i+3));
        map.placeTile(std::make_unique<OpenZone>(i+10, 9));
    }
    for (int i : {0, 1, 2})
        map.placeTile(std::make_unique<OpenZone>(7+i, 5+i));
}

const Map& Game::getMap() const { return map; }

const std::vector<std::unique_ptr<Creature>>& Game::getCreatures() const { return creatures; }

const std::vector<std::unique_ptr<Tower>>& Game::getTowers() const { return towers; }

const unsigned long Game::getTick() const { return tick; }

const Player& Game::getPlayer() const { return player; };

const Cores& Game::getCores() const { return cores; };

const std::vector<std::unique_ptr<VisualEffect>>& Game::getVisualEffects() const { return visualEffects;}

void Game::spawnCreature(std::unique_ptr<Creature> creature) {
    if (map.getEntries().empty() || map.getCoreStorage() == nullptr || map.getExits().empty())
        throw std::runtime_error("Map missing entry or core storage or exit");
    // Assign path (Entry -> CoreStorage or Exit)
    Tile* start = map.getEntries()[0];
    Tile* goal = map.getCoreStorage();

    std::vector<Tile*> path = pathfinder.findPath(start, goal);
    if (path.empty()) path = pathfinder.findPath(start, goal, true);
    creature->setPath(path);
    creature->setPosition({start->getX(), start->getY()});

    creatures.push_back(std::move(creature));
}

PlaceTowerResult Game::placeTower(std::unique_ptr<Tower> tower) {
    Tile* tile = map.getTile(tower->getX(), tower->getY());

    if (!tile->isBuildable())
        return PlaceTowerResult::NotBuildable;
    
    OpenZone* openZoneTile = dynamic_cast<OpenZone*>(tile); // If buildable then the tile is an OpenZone

    if (!player.canAfford(*tower))
        return PlaceTowerResult::NotAffordable;

    player.pay(*tower);
    towers.push_back(std::move(tower));
    openZoneTile->setOccupied(true);

    // Update every creature's path
    for (auto& c : creatures) {
        Tile* start = c->getCurrentTile();
        Tile* goal = c->getDestinationTile();
        std::vector<Tile*> newPath = pathfinder.findPath(start, goal);
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
            
            // CoreStorage reached
            if (CoreStorage* storage = dynamic_cast<CoreStorage*>(current)) {
                if (c->getDestinationTile() == map.getCoreStorage()) {
                    // New path to exit
                    Tile* goal = map.getExits()[0];
                    std::vector<Tile*> newPath = pathfinder.findPath(current, goal);
                    c->setPath(newPath);
                }
            }

            // Exit reached
            else if (ExitZone* exit = dynamic_cast<ExitZone*>(current)) {
                if (c->getDestinationTile() == map.getExits()[0]) {
                    // TODO: make creature diseapear
                    cores.loseCore(c->dropCores());
                }
            }
        }
    }

    // Update visual effects
    for (auto& e : visualEffects)
        e->update(deltaTime);

    // Update towers
    for (auto& t : towers) {
        t->update(deltaTime, creatures);

        // Get visual effects
        std::vector<std::unique_ptr<VisualEffect>> newVisualEffects = t->getVisualEffects();
        if (!newVisualEffects.empty())
            visualEffects.insert(visualEffects.end(), 
                                std::make_move_iterator(newVisualEffects.begin()), 
                                std::make_move_iterator(newVisualEffects.end()));
    }

    // Rewards the player for dead creatures ang return cores to the storage
    for (auto& c : creatures) {
        if (!c->isAlive()) {
            cores.returnCore(c->dropCores());
            player.addMaterials(c->getLoot());
        }
    }

    // Remove dead creatures
    creatures.erase(std::remove_if(creatures.begin(), creatures.end(),
                                   [](const std::unique_ptr<Creature>& c) { return !c->isAlive(); }),
                    creatures.end());

    // Remove "dead" visual effects
    visualEffects.erase(std::remove_if(visualEffects.begin(), visualEffects.end(),
                                       [](auto& e) { return !e->isAlive(); }),
                        visualEffects.end());
}

void Game::render() const {
    std::cout << "Tick: " << tick << "\n";
    //map.printMap();

    for (const auto& c : creatures) {
        if (c->isAlive()) {
            std::array<float, 2> pos = c->getPosition();
            std::string name = c->getTypeName();
            std::cout << name <<  " at (" << pos[0] << "," << pos[1]
                        << ") HP=" << c->getHealth()
                        << " Shield=" << c->getShield() << "\n";
        }
    }
}

bool Game::isGameOver() const {
    bool gameOver = cores.getSafe() == 0 && cores.getStolen() == 0;
    return gameOver;
}
