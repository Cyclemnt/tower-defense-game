#include "core/managers/creatureManager.hpp"

#include "core/events.hpp"
#include "core/map.hpp"
#include "core/interfaces/iPathfinder.hpp"
#include "core/coreStorage.hpp"
#include "core/player.hpp"

namespace tdg::core {

    CreatureManager::CreatureManager(Map& map, IPathfinder& pathfider, CoreStorage& cores, Player& player, std::vector<RoamingCore>& roamingCores)
        : m_map(map), m_pathfinder(pathfider), m_cores(cores), m_player(player), m_roamingCores(roamingCores) {}

    void CreatureManager::update(float dt, Events& events) {
        handleSpawnEvents(events);
        for (CreaturePtr& creature : m_creatures) creature->update(dt, events, m_roamingCores);
        handlePathEvents(events);
        handleDeadCreatures(events);
    }

    void CreatureManager::spawn(Creature::Type type, unsigned int level, std::optional<unsigned int> entry) {
        CreaturePtr newCreature = m_factory.create(type, level);
        if (!newCreature) return;

        // Determine spawn tile
        const Tile* spawnTile = nullptr;
        if (type == Creature::Type::Mother) { // Mother only spawns on exitTiles
            int random = rand() % m_map.exitPoints().size();
            spawnTile = m_map.exitPoints()[random];
        }
        else if (entry.has_value() && entry.value() < m_map.entryPoints().size()) {
            spawnTile = m_map.entryPoints()[entry.value()];
        }
        else {
            int random = rand() % m_map.entryPoints().size();
            spawnTile = m_map.entryPoints()[random];
        }
        // Set creature initial position
        newCreature->setPosition(spawnTile->x, spawnTile->y);

        // Compute initial path
        auto initialPath = m_pathfinder.findPath(spawnTile, m_map.corePoint());
        newCreature->setPath(std::move(initialPath));

        // Add the new creature to the m_creatures
        m_creatures.push_back(std::move(newCreature));
    }

    void CreatureManager::updatePaths() {
        for (CreaturePtr& creature : m_creatures) {
            const Tile* nextTile = creature->nextTile();
            const Tile* destinationTile = creature->destinationTile();

            if (!nextTile || !destinationTile) continue;

            auto path = m_pathfinder.findPath(nextTile, destinationTile);
            creature->setPath(std::move(path));
        }
    }

    void CreatureManager::handleSpawnEvents(Events& events) {
        while (!events.spawn.empty()) {
            Events::Spawn newSpawn = events.spawn.front();
            spawn(newSpawn.type, newSpawn.level, newSpawn.entrance);
            events.sfxs.emplace(Events::NewSFX::Type::CreatureSpawn);
            events.spawn.pop();
        }
    }

    void CreatureManager::handlePathEvents(Events& events) {
        while (!events.onPath.empty()) {
            Events::OnPath& event = events.onPath.front();
            switch (event.type) {

                // Creature reached CoreStorage:
                case Events::OnPath::Type::ArrivedAtCore: {
                    // Steal cores
                    unsigned int capacity = event.creature->remainingCapacity();
                    if (capacity > 0u) {
                        unsigned int stolenCores = m_cores.stealCores(capacity);
                        if (stolenCores > 0u) {
                            event.creature->stealCores(stolenCores);
                            events.sfxs.emplace(Events::NewSFX::Type::CoreSteal);
                        }
                    }
                    // New path to exit
                    std::vector<const Tile*> bestPath = m_pathfinder.findPathToClosestGoal(m_map.corePoint(), m_map.exitPoints());
                    event.creature->setPath(std::move(bestPath));
                    break;
                }

                // Creature reached Exit:
                case Events::OnPath::Type::ReachedExit: {
                    m_cores.loseCores(event.creature->dropCores());
                    event.creature->leave();
                    break;
                }
                
                default: break;
            }
            events.onPath.pop();
        }
    }

    void CreatureManager::handleDeadCreatures(Events& events) {
        for (auto it = m_creatures.begin(); it != m_creatures.end();) {
            CreaturePtr& creature = *it;

            if (!creature->isAlive()) {
                // Return cores and give loot
                events.droppedCores.emplace(creature->dropCores(), creature->px(), creature->py());
                // m_cores.returnCores(creature->dropCores());
                m_player.addMaterials(creature->loot());
                events.sfxs.emplace(Events::NewSFX::Type::CreatureDeath);
                // Erease the creature
                it = m_creatures.erase(it);
            }
            else { ++it; }
        }
    }

} // nameapace tdg::core
