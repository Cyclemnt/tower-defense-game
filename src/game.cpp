#include <iostream>
#include <memory>
#include "../include/game.hpp"
#include "../include/creatures/minion.hpp"
#include "../include/creatures/drone.hpp"
#include "../include/creatures/tank.hpp"
#include "../include/map/coreStorage.hpp"
#include "../include/map/mapLoader.hpp"
#include "../include/map/openZone.hpp"
#include "../include/towers/tower.hpp"
#include "../include/visual-effects/visualEffect.hpp"

Game::Game()
    : map(), pathfinder(map), player(), cores(24), tick(0), waveManager(), paused(false) {

    try {
        MapLoader::loadFromFile(map, "../assets/maps/map1.txt", &cores);
    } catch (const std::exception& e) {
        std::cerr << "[Error] Failed to load map: " << e.what() << std::endl;
    }
}

const Map& Game::getMap() const { return map; }

const std::vector<std::unique_ptr<Creature>>& Game::getCreatures() const { return creatures; }

const std::vector<std::unique_ptr<Tower>>& Game::getTowers() const { return towers; }

const unsigned long Game::getTick() const { return tick; }

const bool Game::isPaused() const { return paused; }

void Game::setPaused(bool pause) { paused = pause; }

void Game::togglePause() { paused = !paused; }

const Player& Game::getPlayer() const { return player; };

const Cores& Game::getCores() const { return cores; };

const std::vector<std::unique_ptr<VisualEffect>>& Game::getVisualEffects() const { return visualEffects;}

void Game::spawnCreature(CreatureType type) {
    std::unique_ptr<Creature> creature;

    switch (type) {
        case CreatureType::Minion:
            creature = std::make_unique<Minion>();
            break;
        case CreatureType::Drone:
            creature = std::make_unique<Drone>();
            break;
        case CreatureType::Tank:
            creature = std::make_unique<Tank>();
            break;
    }

    if (!creature)
        return;

    if (map.getEntries().empty() || map.getCoreStorage() == nullptr)
        throw std::runtime_error("Map missing entry or core storage");

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

    if (openZoneTile->isOccupied()) return PlaceTowerResult::Occupied;

    if (!player.canAfford(*tower))
        return PlaceTowerResult::NotAffordable;

    player.pay(*tower);
    openZoneTile->setOccupied(true);
    // Insert tower depending on other towers y coordinate (to ensure right render order)
    const float newY = static_cast<float>(tower->getY());
    auto it = std::upper_bound(towers.begin(), towers.end(), newY, // upper_bound gives the first tower that getY() > newY so O(log(n))
        [](float y, const std::unique_ptr<Tower>& t) { return y < static_cast<float>(t->getY()); }
    );
    towers.insert(it, std::move(tower)); // is O(log(n)) which gives O(log(n) + n) total time complexity of this sorting

    // Update every creature's path
    updatePaths();

    return PlaceTowerResult::Success;
}

void Game::sellTowerAt(int x, int y) {
    for (auto it = towers.begin(); it != towers.end(); ++it) {
        Tower* tower = it->get();
        if (tower->getX() == x && tower->getY() == y) {
            // Refund: 50% of cost
            std::array<int, 3> price = tower->getPrice();
            for (size_t i = 0; i < price.size(); ++i) { price[i] = static_cast<int>(price[i] * 0.5f); }
            player.getMaterials().add(price);

            // Free the tile
            if (auto* zone = dynamic_cast<OpenZone*>(map.getTile(x, y)))
                zone->setOccupied(false);

            // Remove tower
            towers.erase(it);
            break;
        }
    }

    // Update every creature's path
    updatePaths();
}

void Game::updatePaths() {
    for (auto& c : creatures) {
        Tile* start = c->getCurrentTile();
        Tile* goal = c->getDestinationTile();
        std::vector<Tile*> newPath = pathfinder.findPath(start, goal);
        if (newPath.empty()) newPath = pathfinder.findPath(start, goal, true);
        c->setPath(newPath);
    }
}

void Game::update(float deltaTime) {
    tick++;
    waveManager.update(deltaTime, *this);
    
    // Update creatures
    for (auto& c : creatures) {
        if (c->isAlive()) {

            c->update(deltaTime);

            Tile* current = c->getCurrentTile();
            Tile* destination = c->getDestinationTile();
            
            // CoreStorage reached
            if (destination == map.getCoreStorage() && current == destination) {
                // New path to exit
                Tile* goal = map.getExits()[0];
                std::vector<Tile*> newPath = pathfinder.findPath(current, goal);
                c->setPath(newPath);
            }

            // Exit reached
            else if (destination == map.getExits()[0] && current == destination) {
                cores.loseCore(c->dropCores());
                c->leave();
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

    // Rewards the player for dead creatures and return cores to the storage
    for (auto& c : creatures) {
        if (!c->isAlive()) {
            cores.returnCore(c->dropCores());
            player.addMaterials(c->getLoot());

            // Notify towers
            for (auto& t : towers)
                if (t->getTarget() == c.get())
                    t->clearTarget();
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

bool Game::isGameOver() const {
    bool gameOver = cores.getSafe() == 0 && cores.getStolen() == 0;
    return gameOver;
}
