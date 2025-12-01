#include "engine/game.hpp"
#include "core/events.hpp"

namespace tdg::engine {

    Game::Game(Config cfg)
        : m_map(cfg.mapData), m_waveManager(std::move(cfg.waveSource)), m_pathfinder(cfg.pathfinder), m_player(cfg.startMaterials), m_cores(cfg.startCores) {}

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

        for (PathEvent& pe : m_events.pathEvents) {
            handlePathEvent(pe);
        }

        // Update towers & effects
        for (TowerPtr& t : m_towers) {
            t->update(dt, m_events, m_creatures);
        }

        // Reward and cleanup dead creatures
        handleDeadCreatures();
    }

    void Game::handlePathEvent(PathEvent& pe) {
        switch (pe.type) {

        case PathEvent::Type::ArrivedToCore: {
            int shortestPathLength = std::numeric_limits<int>::max();
            std::vector<const Tile*> shortestPath;

            for (const auto& exitPoint : m_map.exitPoints()) {
                std::vector<const Tile*> newPath =
                    m_pathfinder->findPath(m_map.corePoint(), exitPoint);

                if (newPath.size() < shortestPathLength) {
                    shortestPathLength = (int)newPath.size();
                    shortestPath = std::move(newPath);
                }
            }

            pe.creature->setPath(shortestPath);
            break;
        }

        case PathEvent::Type::ArrivedToExit:
            m_cores.loseCores(pe.creature->dropCores());
            pe.creature->leave();
            break;

        default:
            break;
        }
    }

    void Game::handleDeadCreatures() {
        for (auto it = m_creatures.begin(); it != m_creatures.end();) {

            CreaturePtr& c = *it;

            if (!c->isAlive()) {

                m_cores.returnCores(c->dropCores());
                m_player.addMaterials(c->getLoot());

                // Notify towers if their target died
                for (TowerPtr& t : m_towers)
                    if (t->target() == c.get())
                        t->clearTarget();

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
        if (tile.hasTower) return;

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
        auto it = std::upper_bound(m_towers.begin(), m_towers.end(), newTower->y(),
            [](int y, const TowerPtr& t) { return y < t->y(); });
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
                return;
            }
        }
        
        updatePaths();
    }


    void Game::spawnCreature(Creature::Type type) {
        CreaturePtr newCreature = m_creatureFactory.create(type);
        m_creatures.push_back(newCreature);
        m_events.sfxs.push_back(SFXType::CreatureSpawn);

        // PATH
        // WHERE TO START
        // WHERE TO GO

    }

    bool Game::isGameOver() const { return m_cores.allLost(); }
    bool Game::isVictory() const { return m_waveManager.allWavesCleared() && !isGameOver(); }

} // tdg::engine