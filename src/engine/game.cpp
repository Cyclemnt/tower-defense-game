#include <algorithm>
#include "engine/game.hpp"
#include "infrastructure/aStarPathfinder.hpp"

namespace tdg::engine {

    Game::Game(std::shared_ptr<IMapSource> mapSrc, std::shared_ptr<IWaveSource> waveSrc,
        unsigned int startCores, Materials startMaterials)
        : m_player(startMaterials), m_cores(startCores)
    {
        m_map = std::make_unique<tdg::core::Map>(mapSrc);
        m_map->setCoreStorageFillRatioRequest([this](){ return m_cores.ratio(); });
        m_pathfinder = std::make_unique<tdg::infra::AStarPathfinder>(m_map.get());
        m_waveManager = std::make_unique<tdg::core::WaveManager>(waveSrc);
    }

    void Game::update(float dt) {
        ++m_tick;

        m_waveManager->update(dt, m_events);

        // Spawn new creatures
        while (!m_events.spawn.empty()) {
            Events::Spawn& se = m_events.spawn.front();
            spawnCreature(se.type, se.level, se.entrance);
            m_events.spawn.pop();
        }

        // Create new VFXs
        while (!m_events.vfxs.empty()) {
            Events::VFX& ve = m_events.vfxs.front();
            m_vfxs.push_back(std::move(m_vfxFactory.create(ve)));
            m_events.vfxs.pop();
        }

        // Update visual effects
        for (VFXPtr& v : m_vfxs) v->update(dt);

        // Update creatures
        for (CreaturePtr& c : m_creatures) c->update(dt, m_events);

        // Handle creature's path events
        while (!m_events.path.empty()) handlePathEvent();
        
        // Update towers
        for (TowerPtr& t : m_towers) t->update(dt, m_events, m_creatures);

        // Reward and cleanup dead creatures
        handleDeadCreatures();
        
        // Cleanup dead vfxs
        handleDeadVFX();

        // If no creatures left, load next wave
        if (isWaveOver() && m_waveManager->timeBeforeNext() <= 0.0f) {
            m_waveManager->loadNext();
        }
    }

    void Game::renderVideo(IVideoRenderer& vidRenderer) const {
        m_map->draw(vidRenderer);
        for (const CreaturePtr& c : m_creatures) c->draw(vidRenderer);
        for (const VFXPtr& v : m_vfxs) v->draw(vidRenderer);
        for (const TowerPtr& t : m_towers) t->draw(vidRenderer);
    }

    void Game::renderAudio(IAudioRenderer& audRenderer) {
        while (!m_events.sfxs.empty()) {
            audRenderer.playSound(m_events.sfxs.front().toString());
            m_events.sfxs.pop();
        }
    }

    void Game::handlePathEvent() {
        Events::Path& pe = m_events.path.front();
        switch (pe.type) {
        case Events::Path::Type::ArrivedToCore: {
            std::vector<const Tile*> bestPath = m_pathfinder->findPathToClosestGoal(m_map->corePoint(), m_map->exitPoints());
            pe.creature->stealCores(m_cores.stealCores(pe.creature->remainingCapacity()));
            pe.creature->setPath(std::move(bestPath));
            break;
        }
        case Events::Path::Type::ArrivedToExit: {
            m_cores.loseCores(pe.creature->dropCores());
            pe.creature->leave();
            break;
        }
        default:
            break;
        }
        m_events.path.pop();
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
                m_events.sfxs.emplace(Events::SFX::Type::CreatureDeath);
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

    bool Game::buildTower(Tower::Type type, int x, int y) {
        if (!m_map->canRecieveTowerAt(x, y)) return false;

        // Build the tower
        TowerPtr newTower = m_towerFactory.build(type, x, y);
        if (!newTower) return false;

        // Verify cost
        if (!m_player.canAfford(newTower->cost())) return false;

        // Pay
        m_player.buy(newTower->cost());

        // Mark the tile
        m_map->markTowerAt(x, y);

        // Sorted Insertion
        auto it = std::upper_bound(m_towers.begin(), m_towers.end(), newTower,
            [](const TowerPtr& a, const TowerPtr& b) { return a->y() < b->y(); });
        m_towers.insert(it, std::move(newTower));

        updatePaths();
        return true;
    }

    bool Game::upgradeTower(int x, int y) {
        if (!m_map->hasTowerAt(x, y)) return false;

        for (auto it = m_towers.begin(); it != m_towers.end(); ++it) {
            TowerPtr& t = *it;

            if (t->x() == x && t->y() == y) {
                if (!m_player.canAfford(t->upgradeCost())) return false;

                m_player.buy(t->upgradeCost());
                t->upgrade();

                return true;
            }
        }
        return false;
    }

    bool Game::sellTower(int x, int y) {
        if (!m_map->hasTowerAt(x, y)) return false;

        for (auto it = m_towers.begin(); it != m_towers.end(); ++it) {
            TowerPtr& t = *it;

            if (t->x() == x && t->y() == y) {
                m_player.addMaterials(t->sellValue());
                m_map->removeTowerAt(x, y);

                m_towers.erase(it);
                updatePaths();
                return true;
            }
        }
        return false;
    }

    void Game::spawnCreature(Creature::Type type, unsigned int level, std::optional<unsigned int> entry) {
        CreaturePtr newCreature = m_creatureFactory.create(type, level);
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
        m_events.sfxs.emplace(Events::SFX::Type::CreatureSpawn);
    }

    void Game::updatePaths() {
        for (CreaturePtr& creature : m_creatures) {
            const Tile* nextTile = creature->nextTile();
            const Tile* destinationTile = creature->destinationTile();

            if (!nextTile || !destinationTile) continue;

            auto path = m_pathfinder->findPath(nextTile, destinationTile);
            creature->setPath(std::move(path));
        }
    }
    
    bool Game::isWaveOver() const { return m_creatures.empty(); }
    bool Game::isGameOver() const { return m_cores.allLost(); }
    bool Game::isVictory() const { return m_waveManager->allWavesSpawned() && isWaveOver() && !isGameOver(); }

    /* Everything after this is an answer to bad time management, this is very ugly */
    
    GameView Game::getView() const {
        return {
            m_player.materials(),
            m_cores.safeCount(), m_cores.stolenCount(), m_cores.lostCount(),
            m_waveManager->waveIndex(), m_waveManager->waveCount(), m_waveManager->timeBeforeNext()
        };
    }

    void Game::buildTower(std::string towerType, int x, int y) {
        if (towerType == "Gatling") buildTower(Tower::Type::Gatling, x, y);
        if (towerType == "Mortar") buildTower(Tower::Type::Mortar, x, y);
        if (towerType == "Laser") buildTower(Tower::Type::Laser, x, y);
    }

    bool Game::canAfford(std::string towerType) const {
        if (towerType == "Gatling") return canAfford(Tower::Type::Gatling);
        if (towerType == "Mortar") return canAfford(Tower::Type::Mortar);
        if (towerType == "Laser") return canAfford(Tower::Type::Laser);
        return false;
    }
    
    bool Game::canAfford(Tower::Type type) const {
        TowerPtr temp = m_towerFactory.build(type, -1, -1);
        return m_player.canAfford(temp->cost());
    }

    std::optional<float> Game::towerRangeAt(int x, int y) const {
        for (auto it = m_towers.begin(); it != m_towers.end(); ++it) {
            const TowerPtr& t = *it;
            if (t->x() == x && t->y() == y) {
                return t->stats().range;
            }
        }
        return std::nullopt;
    }

    bool Game::tileOpenAt(int x, int y) const {
        Tile* tile = m_map->tileAt(x, y);
        if (!tile) return false;
        if (tile->type == Tile::Type::Open) return true;
        else return false;
    }

    bool Game::towerAt(int x, int y) const {
        Tile* tile = m_map->tileAt(x, y);
        if (!tile) return false;
        if (tile->hasTower) return true;
        else return false;
    }

    std::optional<Materials> Game::towerCost(std::string towerType) const {
        if (towerType == "Gatling") return towerCost(Tower::Type::Gatling);
        if (towerType == "Mortar") return towerCost(Tower::Type::Mortar);
        if (towerType == "Laser") return towerCost(Tower::Type::Laser);
        return std::nullopt;
    }
    
    std::optional<Materials> Game::towerCost(Tower::Type type) const {
        TowerPtr temp = m_towerFactory.build(type, -1, -1);
        return temp->cost();
    }

} // tdg::engine