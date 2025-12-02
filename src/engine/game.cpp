#include "engine/game.hpp"
#include "core/events.hpp"

namespace tdg::engine {

    Game::Game(Config cfg)
        : m_map(std::move(cfg.mapData))
        , m_waveManager(std::move(cfg.waveSource))
        , m_pathfinder(std::move(cfg.pathfinder))
        , m_player(std::move(cfg.startMaterials))
        , m_cores(cfg.startCores) {}

    void Game::update(float dt) {
        if (m_paused) return;
        // dt *= speed;
        ++tick;

        m_waveManager.update(dt);

        // Update events with a lifetime
        m_events.update(dt);

        // Update creatures
        for (CreaturePtr& c : m_creatures) {
            c->update(dt, m_events);
        }

        // Handle creature's path events
        for (PathEvent& pe : m_events.pathEvents) {
            handlePathEvent(pe);
        }

        // Update towers
        for (TowerPtr& t : m_towers) {
            t->update(dt, m_events, m_creatures);
        }

        // Reward and cleanup dead creatures
        handleDeadCreatures();
    }

    void Game::handlePathEvent(PathEvent& pe) {
        switch (pe.type) {

        case PathEvent::Type::ArrivedToCore: {
            std::vector<const Tile*> bestPath = m_pathfinder->findPathToClosestGoal(m_map.corePoint(), m_map.exitPoints());
            pe.creature->setPath(std::move(bestPath));
            break;
        }
        case PathEvent::Type::ArrivedToExit: {
            m_cores.loseCores(pe.creature->dropCores());
            pe.creature->leave();
            break;
        }
        default:
            break;
        }
    }

    void Game::handleDeadCreatures() {
        for (auto it = m_creatures.begin(); it != m_creatures.end();) {
            CreaturePtr& c = *it;

            if (!c->isAlive()) {

                m_cores.returnCores(c->dropCores());
                m_player.addMaterials(c->loot());

                // Notify towers if their target died
                for (TowerPtr& t : m_towers) {
                    if (t->target() == c.get())
                        t->clearTarget();
                }
                
                it = m_creatures.erase(it);
                m_events.sfxs.push_back(SFXType::CreatureDeath);
            }
            else {
                ++it;
            }
        }
    }

    void Game::buildTower(Tower::Type type, int x, int y) {
        Tile& tile = *m_map.tileAt(x, y);

        if (!tile.buildable()) return;

        // Build the tower
        TowerPtr newTower = m_towerFactory.build(type, x, y);
        if (!newTower) return;

        // Verify cost
        if (!m_player.canAfford(newTower->cost()))
            return;

        // Pay
        m_player.buy(newTower->cost());

        // Mark the tile
        tile.hasTower = true;

        // Sorted Insertion
        auto it = std::upper_bound(m_towers.begin(), m_towers.end(), newTower,
            [](const TowerPtr& a, const TowerPtr& b) { return a->y() < b->y(); });
        m_towers.insert(it, std::move(newTower));

        updatePaths();
    }

    void Game::sellTower(int x, int y) {
        Tile& tile = *m_map.tileAt(x, y);

        if (!tile.sellable()) return;

        for (auto it = m_towers.begin(); it != m_towers.end(); ++it) {
            TowerPtr& t = *it;

            if (t->x() == x && t->y() == y) {

                m_player.addMaterials(t->sellValue());
                tile.hasTower = false;

                m_towers.erase(it);
                updatePaths();
                return;
            }
        }

        // nothing sold
    }

    void Game::spawnCreature(Creature::Type type) {
        CreaturePtr newCreature = m_creatureFactory.create(type);
        if (!newCreature) return;

        const Tile* spawnTile = nullptr;
        if (!m_map.entryPoints().empty())
            spawnTile = m_map.entryPoints().front();

        // Set creature initial position
        newCreature->setPosition(spawnTile->x, spawnTile->y);

        // Compute initial path
        auto initialPath = m_pathfinder->findPath(spawnTile, m_map.corePoint());
        if (!initialPath.empty())
            newCreature->setPath(std::move(initialPath));

        m_creatures.emplace_back(std::move(newCreature));
        m_events.sfxs.push_back(SFXType::CreatureSpawn);
    }

    void Game::updatePaths() {
        for (CreaturePtr& creature : m_creatures) {
            const Tile* nextTile = creature->nextTile();
            const Tile* destinationTile = creature->destinationTile();
            if (!nextTile) continue;
            auto path = m_pathfinder->findPath(nextTile, destinationTile);
            creature->setPath(std::move(path));
        }
    }

    bool Game::isGameOver() const { return m_cores.allLost(); }
    bool Game::isVictory() const { return m_waveManager.allWavesCleared() && !isGameOver(); }

} // tdg::engine