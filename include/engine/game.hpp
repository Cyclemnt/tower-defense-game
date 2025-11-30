#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>
#include <chrono>
#include "core/map.hpp"
#include "core/waveManager.hpp"
#include "core/player.hpp"
#include "core/coreStorage.hpp"
#include "core/towers/tower.hpp"
#include "core/creatures/creature.hpp"
#include "core/interfaces/iPathfinder.hpp"
#include "core/events.hpp"

namespace tdg::infra { class IRenderer; } // forward decl of infra interface

namespace tdg::engine {

    using namespace tdg::core;

    class Game {
    public:
        struct Config {
            MapData mapData;
            std::unique_ptr<IWaveSource> waveSource;
            std::shared_ptr<IPathfinder> pathfinder;
            Materials startMaterials;
            unsigned int startCores;
        };

        Game(Config cfg);

        void update(float dt);
        // void render(tdg::infra::IRenderer& renderer);

        bool buildTower(const std::string& towerId, int x, int y);
        void sellTower(int x, int y);

        void spawnCreature();

        bool isGameOver() const;
        bool isVictory() const;

    private:
        bool m_paused{false};
        unsigned long tick{0};
        
        Map m_map;
        WaveManager m_waveManager;
        Player m_player;
        CoreStorage m_cores;

        std::vector<TowerPtr> m_towers;
        std::vector<CreaturePtr> m_creatures;
        Events m_events;

        std::shared_ptr<IPathfinder> m_pathfinder;
    };

} // namespace tdg::engine

#endif // GAME_HPP