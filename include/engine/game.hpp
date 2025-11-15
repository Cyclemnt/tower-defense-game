#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>
#include <chrono>
#include "core/map.hpp"
#include "core/waveManager.hpp"
#include "core/player.hpp"
#include "core/coreStorage.hpp"
#include "core/tower.hpp"
#include "core/creature.hpp"
#include "core/interfaces/iPathfinder.hpp"

namespace tdg::infra { class IRenderer; } // forward decl of infra interface

namespace tdg::engine {

    using namespace tdg::core;

    class Game {
    public:
        struct Config {
            MapData mapData;
            std::unique_ptr<IWaveSource> waveSource;
            Materials startingMaterials;
        };

        Game(Config cfg, std::shared_ptr<IPathfinder> pathfinder);

        void update(std::chrono::milliseconds dt);
        void render(tdg::infra::IRenderer& renderer);

        bool buildTower(const std::string& towerId, int x, int y);
        bool sellTower(int x, int y);

        bool isGameOver() const;
        bool isVictory() const;

    private:
        Map m_map;
        WaveManager m_waveManager;
        Player m_player;
        CoreStorage m_cores;
        std::vector<TowerPtr> m_towers;
        std::vector<CreaturePtr> m_creatures;
        std::shared_ptr<IPathfinder> m_pathfinder;
    };

} // namespace tdg::engine

#endif // GAME_HPP