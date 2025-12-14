#include <algorithm>
#include "engine/game.hpp"
#include "infrastructure/aStarPathfinder.hpp"

namespace tdg::engine {

    Game::Game(std::shared_ptr<IMapSource> mapSrc, std::shared_ptr<IWaveSource> waveSrc,
        unsigned int startCores, Materials startMaterials)
        : m_player(startMaterials), m_cores(startCores)
    {
        m_map = std::make_unique<tdg::core::Map>(mapSrc);
        m_pathfinder = std::make_unique<tdg::infra::AStarPathfinder>(m_map.get());
        m_waveManager = std::make_unique<tdg::core::WaveManager>(waveSrc);
    }

    void Game::update(float dt) {
        ++tick;

        m_waveManager->update(dt, m_events);

        // Spawn new creatures
        while (!m_events.spawn.empty()) {
            SpawnInfo& se = m_events.spawn.front();
            spawnCreature(se.type, se.entrance);
            m_events.spawn.pop();
        }

        // Create new VFXs
        while (!m_events.vfxs.empty()) {
            VFXEventData& ve = m_events.vfxs.front();
            m_vfxs.push_back(std::move(m_vfxFactory.create(ve)));
            m_events.vfxs.pop();
        }

        // Update visual effects
        for (VFXPtr& v : m_vfxs) v->update(dt);

        // Update creatures
        for (CreaturePtr& c : m_creatures) c->update(dt, m_events);

        // Handle creature's path events
        while (!m_events.pathEvents.empty()) handlePathEvent();
        
        // Update towers
        for (TowerPtr& t : m_towers) t->update(dt, m_events, m_creatures);

        // Reward and cleanup dead creatures
        handleDeadCreatures();
        
        // Cleanup dead vfxs
        handleDeadVFX();

        // If no creatures left, load next wave
        if (isWaveOver() && m_waveManager->getTimeBeforeNext() <= 0.0f) {
            m_waveManager->loadNext();
        }

        // Update core storage fill ratio
        m_map->setCoreStorageFillRatio(m_cores.ratio());
    }

    void Game::render(IVideoRenderer& vidRenderer) const {
        m_map->draw(vidRenderer);
        for (const CreaturePtr& c : m_creatures) c->draw(vidRenderer);
        for (const TowerPtr& t : m_towers) t->draw(vidRenderer);
        for (const VFXPtr& v : m_vfxs) v->draw(vidRenderer);
    }

    void Game::handlePathEvent() {
        PathEvent& pe = m_events.pathEvents.front();
        switch (pe.type) {
        case PathEvent::Type::ArrivedToCore: {
            std::vector<const Tile*> bestPath = m_pathfinder->findPathToClosestGoal(m_map->corePoint(), m_map->exitPoints());
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
        m_events.pathEvents.pop();
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
                m_events.sfxs.push(SFXType::CreatureDeath);
            }
            else {
                ++it;
            }
        }
    }

    void Game::handleDeadVFX() {
        for (auto it = m_vfxs.begin(); it != m_vfxs.end();) {
            VFXPtr& v = *it;
            if (!v->isAlive()) it = m_vfxs.erase(it);
            else ++it;
        }
    }

    void Game::buildTower(Tower::Type type, int x, int y) {
        Tile* tile = m_map->tileAt(x, y);
        if (!tile) return;
        if (!tile->buildable()) return;

        // Build the tower
        TowerPtr newTower = m_towerFactory.build(type, x, y);
        if (!newTower) return;

        // Verify cost
        if (!m_player.canAfford(newTower->cost())) return;

        // Pay
        m_player.buy(newTower->cost());

        // Mark the tile
        tile->hasTower = true;

        // Sorted Insertion
        auto it = std::upper_bound(m_towers.begin(), m_towers.end(), newTower,
            [](const TowerPtr& a, const TowerPtr& b) { return a->y() < b->y(); });
        m_towers.insert(it, std::move(newTower));

        updatePaths();
    }

    void Game::upgradeTower(int x, int y) {
        // TODO
    }

    void Game::sellTower(int x, int y) {
        Tile* tile = m_map->tileAt(x, y);
        if (!tile) return;
        if (!tile->sellable()) return;

        for (auto it = m_towers.begin(); it != m_towers.end(); ++it) {
            TowerPtr& t = *it;

            if (t->x() == x && t->y() == y) {
                m_player.addMaterials(t->sellValue());
                tile->hasTower = false;

                m_towers.erase(it);
                updatePaths();
                return;
            }
        }

        // nothing sold
    }

    void Game::spawnCreature(Creature::Type type, std::optional<unsigned int> entry) {
        CreaturePtr newCreature = m_creatureFactory.create(type);
        if (!newCreature) return;

        const Tile* spawnTile = nullptr;
        if (entry.has_value() && entry.value() < m_map->entryPoints().size()) {
            spawnTile = m_map->entryPoints()[entry.value()];
        }
        else {
            int random = rand() % m_map->entryPoints().size();
            spawnTile = m_map->entryPoints()[random];
        }
        // Set creature initial position
        newCreature->setPosition(spawnTile->x, spawnTile->y);

        // Compute initial path
        auto initialPath = m_pathfinder->findPath(spawnTile, m_map->corePoint());
        if (!initialPath.empty())
            newCreature->setPath(std::move(initialPath));

        m_creatures.push_back(std::move(newCreature));
        m_events.sfxs.push(SFXType::CreatureSpawn);
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

    bool Game::isWaveOver() const { return m_creatures.empty(); }
    bool Game::isGameOver() const { return m_cores.allLost(); }
    bool Game::isVictory() const { return m_waveManager->allWavesSpawned() && isWaveOver() && !isGameOver(); }

} // tdg::engine