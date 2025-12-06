#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>
#include "core/waveManager.hpp"
#include "core/player.hpp"
#include "core/coreStorage.hpp"
#include "core/towers/tower.hpp"
#include "core/creatures/creature.hpp"
#include "core/events.hpp"
#include "core/factories/towerFactory.hpp"
#include "core/factories/creatureFactory.hpp"

// forward declarations
namespace tdg::core { class Map; }
namespace tdg::core { class IPathfinder; }
// namespace tdg::core { class WaveManager; }

namespace tdg::engine {

    using namespace tdg::core;

    class Game {
    public:
        explicit Game(std::shared_ptr<IMapSource> mapSrc, std::shared_ptr<IWaveSource> waveSrc,
            unsigned int startCores = 24u, Materials startMaterials = {100u,100u,100u});

        void update(float dt);

        void buildTower(Tower::Type type, int x, int y);
        void upgradeTower(int x, int y);
        void sellTower(int x, int y);

        void spawnCreature(Creature::Type type, std::optional<unsigned int> entry);

        bool isWaveOver() const;
        bool isGameOver() const;
        bool isVictory() const;

    private:
        void handlePathEvent();
        void handleDeadCreatures();
        void updatePaths();
        
        bool m_paused{false};
        unsigned long tick{0};
        
        std::unique_ptr<Map> m_map;
        std::unique_ptr<IPathfinder> m_pathfinder;
        std::unique_ptr<WaveManager> m_waveManager;
        
        Player m_player;
        CoreStorage m_cores;

        std::vector<TowerPtr> m_towers;
        std::vector<CreaturePtr> m_creatures;
        Events m_events;

        TowerFactory m_towerFactory;
        CreatureFactory m_creatureFactory;
    };

} // namespace tdg::engine

#endif // GAME_HPP