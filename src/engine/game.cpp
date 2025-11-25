#include "engine/game.hpp"

namespace tdg::engine {

    Game::Game(Config cfg, std::shared_ptr<IPathfinder> pathfinder)
        : m_map(cfg.mapData), m_waveManager(std::move(cfg.waveSource)), m_pathfinder(pathfinder), m_player({0u,0u,100u}), m_cores(24u) {}

    void Game::update(std::chrono::milliseconds dt) {
        if (m_paused) return;
        dt *= speed;
        ++tick;

        m_waveManager.update(dt);

        // Update creatures
        for (std::unique_ptr<Creature>& c : m_creatures) {
            c->update(dt);
        }

        // Update towers & effects
        for (std::unique_ptr<Tower>& t : m_towers) {
            if (isOver()) t->clearTarget();
            else {
                t->update(dt, m_creatures);
                auto newEffects = t->getVisualEffects();
                if (!newEffects.empty()) {
                    visualEffects.insert(visualEffects.end(),
                        std::make_move_iterator(newEffects.begin()),
                        std::make_move_iterator(newEffects.end()));
                }
            }
        }

        // Update all visual effects
        for (std::unique_ptr<VisualEffect>& e : visualEffects)
            e->update(dt);

        // Reward and cleanup dead creatures
        for (std::unique_ptr<Creature>& c : m_creatures) {
            if (!c->isAlive()) {
                m_cores.returnCores(c->dropCores());
                m_player.addMaterials(c->getLoot());
                for (std::unique_ptr<Tower>& t : m_towers)
                    if (t->getTarget() == c.get())
                        t->clearTarget();
            }
        }

        m_creatures.erase(
            std::remove_if(m_creatures.begin(), m_creatures.end(),
                [](const auto& c) { return !c->isAlive(); }),
            m_creatures.end());

        visualEffects.erase(
            std::remove_if(visualEffects.begin(), visualEffects.end(),
                [](const auto& e) { return !e->isAlive(); }),
            visualEffects.end());
    }

    void Game::render(tdg::infra::IRenderer& renderer);

    bool Game::buildTower(const std::string& towerId, int x, int y);
    bool Game::sellTower(int x, int y);

    bool Game::isGameOver() const;
    bool Game::isVictory() const;

} // tdg::engine