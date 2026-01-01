#include <algorithm>
#include "engine/game.hpp"
#include "infrastructure/aStarPathfinder.hpp"

#include "core/interfaces/iVideoRenderer.hpp"
#include "core/interfaces/iAudioRenderer.hpp"

namespace tdg::engine {

    Game::Game(std::shared_ptr<IMapSource> mapSrc, std::shared_ptr<IWaveSource> waveSrc, unsigned int startCores, Materials startMaterials)
        : m_player(startMaterials), m_cores(startCores),
        m_map(std::make_unique<tdg::core::Map>(mapSrc)),
        m_pathfinder(std::make_unique<tdg::infra::AStarPathfinder>(*m_map)),
        m_waveManager(std::make_unique<tdg::core::WaveManager>(waveSrc)),

        m_roamingCoreManager(*m_map, *m_pathfinder, m_cores),
        m_creatureManager(*m_map, *m_pathfinder, m_cores, m_player, m_roamingCoreManager.roamingCores()),
        m_towerManager(*m_map, m_player, m_creatureManager.creatures()),
        m_vfxManager(),
        m_sfxManager(m_events.sfxs)
    {
        m_map->setCoreStorageFillRatioRequest([this](){ return m_cores.ratio(); });
    }

    void Game::update(float dt) {
        ++m_tick;

        // Update WaveManager
        m_waveManager->update(dt, m_events);

        // Create and update VFXs
        m_vfxManager.update(dt, m_events);

        // Create and update creatures
        m_creatureManager.update(dt, m_events);

        // Create and update roaming cores
        m_roamingCoreManager.update(dt, m_events);
        
        // Update towers
        m_towerManager.update(dt, m_events);

        // If no creatures left, load next wave
        if (isWaveOver() && !isGameOver()) {
            m_waveManager->loadNext();
            m_events.sfxs.emplace(Events::NewSFX::Type::NextWave);
        }

        // if (isGameOver()) m_events.sfxs.emplace(Events::NewSFX::Type::GameOver);
        // if (isVictory()) m_events.sfxs.emplace(Events::NewSFX::Type::LevelCompleted);
    }

    void Game::renderVideo(IVideoRenderer& vidRenderer) const {
        // Draw Map first
        m_map->draw(vidRenderer);

        // Make Renderable vector
        std::vector<const Renderable*> renderables;
        renderables.reserve(
          m_creatureManager.creatures().size()
          + m_towerManager.towers().size()
          + m_vfxManager.vfxs().size()
        );

        // Fill Renderable vector objetcs
        for (const auto& c : m_creatureManager.creatures()) renderables.push_back(c.get());
        for (const auto& t : m_towerManager.towers())    renderables.push_back(t.get());
        for (const auto& v : m_vfxManager.vfxs())        renderables.push_back(v.get());

        std::stable_sort(renderables.begin(), renderables.end(),
                        [](const Renderable* a, const Renderable* b) {
                            float za = a->zOrder();
                            float zb = b->zOrder();
                            float diff = za - zb;
                            if ((diff < 0 ? -diff : diff) > 0.1f) return za < zb;
                            // if same zOrder (+|-0.1) : tie-breaker over drawLayer()
                            return a->drawLayer() < b->drawLayer();
                        });

        // Draw in order
        for (const Renderable* r : renderables) r->draw(vidRenderer);

        for (const auto& r : m_roamingCoreManager.roamingCores()) r.draw(vidRenderer);
    }

    void Game::renderAudio(IAudioRenderer& audRenderer) {
        m_sfxManager.renderAudio(audRenderer);
    }

    bool Game::buildTower(std::string towerType, int x, int y) {
        if (isGameOver()) return false;
        bool towerBuilt = false;
        if (towerType == "Gatling") towerBuilt = m_towerManager.buildTower(Tower::Type::Gatling, x, y);
        if (towerType == "Mortar") towerBuilt = m_towerManager.buildTower(Tower::Type::Mortar, x, y);
        if (towerType == "Laser") towerBuilt = m_towerManager.buildTower(Tower::Type::Laser, x, y);
        if (towerBuilt) m_creatureManager.updatePaths();
        return towerBuilt;
    }

    bool Game::upgradeTower(int x, int y) {
        if (isGameOver()) return false;
        bool towerUpgraded = false;
        towerUpgraded = m_towerManager.upgradeTower(x, y);
        return towerUpgraded;
    }

    bool Game::sellTower(int x, int y) {
        if (isGameOver()) return false;
        bool towerSold = false;
        towerSold = m_towerManager.sellTower(x, y);
        if (towerSold) m_creatureManager.updatePaths();
        return towerSold;
    }

    void Game::spawnCreature(std::string creatureType, unsigned int level, std::optional<unsigned int> entry) {
        if (isGameOver()) return;
        if (creatureType == "Minion") m_creatureManager.spawn(Creature::Type::Minion, level, entry);
        if (creatureType == "Drone") m_creatureManager.spawn(Creature::Type::Drone, level, entry);
        if (creatureType == "Tank") m_creatureManager.spawn(Creature::Type::Tank, level, entry);
    }
    
    bool Game::isWaveOver() const { return m_creatureManager.noCreature() && m_waveManager->waveFinished(); }
    bool Game::isGameOver() const { return m_cores.allLost(); }
    bool Game::isVictory() const { return m_waveManager->allWavesSpawned() && isWaveOver() && !isGameOver(); }

    bool Game::canAfford(std::string towerType) const {
        if (isGameOver()) return false;
        std::optional<Materials> cost = towerCost(towerType);
        if (cost.has_value()) return m_player.canAfford(cost.value());
        else return false;
    }

    std::optional<float> Game::towerRangeAt(int x, int y) const {
        if (isGameOver()) return std::nullopt;
        return m_towerManager.towerRangeAt(x, y);
    }

    bool Game::tileOpenAt(int x, int y) const {
        if (isGameOver()) return false;
        Tile* tile = m_map->tileAt(x, y);
        if (!tile) return false;
        if (tile->type == Tile::Type::Open) return true;
        else return false;
    }

    bool Game::towerAt(int x, int y) const {
        if (isGameOver()) return false;
        Tile* tile = m_map->tileAt(x, y);
        if (!tile) return false;
        if (tile->hasTower) return true;
        else return false;
    }

    std::optional<Materials> Game::towerCost(std::string towerType) const {
        if (towerType == "Gatling") return TowerFactory::getCost(Tower::Type::Gatling);
        if (towerType == "Mortar") return TowerFactory::getCost(Tower::Type::Mortar);
        if (towerType == "Laser") return TowerFactory::getCost(Tower::Type::Laser);
        return std::nullopt;
    }

    Materials Game::playerBalance() const noexcept { return m_player.materials(); }
    CoresState Game::coresState() const noexcept { return { m_cores.safeCount(), m_cores.stolenCount(), m_cores.lostCount() }; }
    WaveState Game::waveState() const noexcept { return { m_waveManager->waveIndex(), m_waveManager->waveCount(), m_waveManager->timeBeforeNext() }; }

} // tdg::engine