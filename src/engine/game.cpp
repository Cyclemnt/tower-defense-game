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

        // Update creatures
        for (CreaturePtr& c : m_creatures) {
            c->update(dt);
        }

        // Update towers & effects
        for (TowerPtr& t : m_towers) {
            t->update(dt, m_events, m_creatures);
        }

        // Update events with a lifetime
        m_events.update(dt);

        // Reward and cleanup dead creatures
        for (auto it = m_creatures.begin(); it != m_creatures.end(); ) {
            CreaturePtr& c = *it;
            if (!c->isAlive()) {
                m_cores.returnCores(c->dropCores());
                m_player.addMaterials(c->getLoot());
                // Notify Tower in caase of target death
                for (TowerPtr& t : m_towers) if (t->target() == c.get()) t->clearTarget();
                it = m_creatures.erase(it);
                m_events.sfxs.push_back(SFXType::CreatureDeath);
            }
            else { ++it; }
        }
    }

    void Game::render(tdg::infra::IRenderer& renderer) {}

    bool Game::buildTower(const std::string& towerId, int x, int y) {}
    void Game::sellTower(int x, int y) {}

    void Game::spawnCreature() {
        m_events.sfxs.push_back(SFXType::CreatureSpawn);
    }

    bool Game::isGameOver() const { return m_cores.allLost(); }
    bool Game::isVictory() const {}

} // tdg::engine