#include <algorithm>
#include <stdexcept>
#include "../include/game.hpp"

#include "../include/creatures/minion.hpp"
#include "../include/creatures/drone.hpp"
#include "../include/creatures/tank.hpp"
#include "../include/tiles/coreStorage.hpp"
#include "../include/tiles/openZone.hpp"
#include "../include/waves/jsonWaveSource.hpp"
#include "../include/waves/autoWaveSource.hpp"
#include "../include/map/txtMapSource.hpp"

Game::Game()
    : map(std::make_unique<TxtMapSource>("../assets/maps/map1.txt"), &cores),
      pathfinder(map),
      player(),
      cores(),
      waveManager(std::make_unique<WaveManager>(std::make_unique<AutoWaveSource>())) 
{
    // Optionally, load from JSON:
    // waveManager = std::make_unique<WaveManager>(
    //     std::make_unique<JsonWaveSource>("../assets/waves/level1.json"));
}

void Game::spawnCreature(Creature::Type type) {
    std::unique_ptr<Creature> creature;

    switch (type) {
        case Creature::Type::Minion:  creature = std::make_unique<Minion>(); break;
        case Creature::Type::MinionB: creature = std::make_unique<Minion>(true); break;
        case Creature::Type::Drone:   creature = std::make_unique<Drone>(); break;
        case Creature::Type::DroneB:  creature = std::make_unique<Drone>(true); break;
        case Creature::Type::Tank:    creature = std::make_unique<Tank>(); break;
        case Creature::Type::TankB:   creature = std::make_unique<Tank>(true); break;
    }

    if (!creature) return;
    if (map.getEntries().empty() || map.getCoreStorage() == nullptr)
        throw std::runtime_error("[Game] Map missing entry or core storage.");

    const Tile* start = map.getEntries().front();
    const Tile* goal = map.getCoreStorage();

    std::vector<const Tile*> path = pathfinder.findPath(start, goal);
    if (path.empty())
        path = pathfinder.findPath(start, goal, true);

    creature->setPath(path);
    creature->setPosition(start->getPosition());
    creatures.push_back(std::move(creature));
}

PlaceTowerResult Game::placeTower(std::unique_ptr<Tower> tower) {
    Tile* tile = map.getTile(tower->getPosition());
    if (!tile || !tile->isBuildable()) return PlaceTowerResult::NotBuildable;

    OpenZone* openZone = dynamic_cast<OpenZone*>(tile);
    if (openZone->isOccupied()) return PlaceTowerResult::Occupied;
    if (!player.canAfford(*tower)) return PlaceTowerResult::NotAffordable;

    player.buy(*tower);
    openZone->setOccupied(true);

    // Insert tower sorted by Y for correct draw order
    const float newY = static_cast<float>(tower->getPosition().y);
    auto it = std::upper_bound(
        towers.begin(), towers.end(), newY,
        [](float y, const std::unique_ptr<Tower>& t) {
            return y < static_cast<float>(t->getPosition().y);
        });
    towers.insert(it, std::move(tower));

    updatePaths();
    return PlaceTowerResult::Success;
}

void Game::sellTowerAt(sf::Vector2i position) {
    for (auto it = towers.begin(); it != towers.end(); ++it) {
        Tower* tower = it->get();
        if (tower->getPosition() == position) {
            player.addMaterials(tower->getCost() * 0.5f); // refund
            if (OpenZone* zone = dynamic_cast<OpenZone*>(map.getTile(position)))
                zone->setOccupied(false);
            towers.erase(it);
            updatePaths();
            return;
        }
    }
}

void Game::updatePaths() {
    for (std::unique_ptr<Creature>& c : creatures) {
        const Tile* start = c->getCurrentTile();
        const Tile* goal = c->getDestinationTile();
        std::vector<const Tile*> newPath = pathfinder.findPath(start, goal);
        if (newPath.empty()) newPath = pathfinder.findPath(start, goal, true);
        c->setPath(newPath);
    }
}

void Game::update(float deltaTime) {
    if (paused) return;
    ++tick;
    waveManager->update(deltaTime, *this);

    // Update creatures
    for (std::unique_ptr<Creature>& c : creatures) {
        if (!c->isAlive()) continue;
        c->update(deltaTime);

        const Tile* current = c->getCurrentTile();
        const Tile* dest = c->getDestinationTile();

        if (dest == map.getCoreStorage() && current == dest) {
            const Tile* exit = map.getExits().front();
            std::vector<const Tile*> newPath = pathfinder.findPath(current, exit);
            c->setPath(newPath);
        } 
        else if (dest == map.getExits().front() && current == dest) {
            cores.loseCore(c->dropCores());
            c->leave();
        }
    }

    // Update towers & effects
    for (std::unique_ptr<Tower>& t : towers) {
        t->update(deltaTime, creatures);
        auto newEffects = t->getVisualEffects();
        if (!newEffects.empty()) {
            visualEffects.insert(visualEffects.end(),
                std::make_move_iterator(newEffects.begin()),
                std::make_move_iterator(newEffects.end()));
        }
    }

    // Update all visual effects
    for (std::unique_ptr<VisualEffect>& e : visualEffects)
        e->update(deltaTime);

    // Reward and cleanup dead creatures
    for (std::unique_ptr<Creature>& c : creatures) {
        if (!c->isAlive()) {
            cores.returnCore(c->dropCores());
            player.addMaterials(c->getLoot());
            for (std::unique_ptr<Tower>& t : towers)
                if (t->getTarget() == c.get())
                    t->clearTarget();
        }
    }

    creatures.erase(
        std::remove_if(creatures.begin(), creatures.end(),
            [](const auto& c) { return !c->isAlive(); }),
        creatures.end());

    visualEffects.erase(
        std::remove_if(visualEffects.begin(), visualEffects.end(),
            [](const auto& e) { return !e->isAlive(); }),
        visualEffects.end());
}

bool Game::isGameOver() const noexcept {
    return cores.getSafe() == 0 && cores.getStolen() == 0;
}
