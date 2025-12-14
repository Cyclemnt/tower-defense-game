#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>
#include <optional>

#include "core/map.hpp"
#include "core/interfaces/iPathfinder.hpp"
#include "core/waveManager.hpp"

#include "core/player.hpp"
#include "core/coreStorage.hpp"

#include "core/towers/tower.hpp"
#include "core/creatures/creature.hpp"
#include "core/vfxs/vfx.hpp"
#include "core/events.hpp"

#include "core/factories/towerFactory.hpp"
#include "core/factories/creatureFactory.hpp"
#include "core/factories/vfxFactory.hpp"

#include "core/interfaces/iVideoRenderer.hpp"
#include "core/interfaces/iAudioRenderer.hpp"

namespace tdg::core { class IWaveSource; }
namespace tdg::core { class IMapSource; }

namespace tdg::engine {

    using namespace tdg::core;

    class Game {
    public:
        explicit Game(std::shared_ptr<IMapSource> mapSrc, std::shared_ptr<IWaveSource> waveSrc,
            unsigned int startCores = 24u, Materials startMaterials = {100u,100u,100u});

        void update(float dt);
        void render(IVideoRenderer& renderer) const;

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
        void handleDeadVFX();
        void updatePaths();
        
        unsigned long tick{0u};
        
        std::unique_ptr<Map> m_map;
        std::unique_ptr<IPathfinder> m_pathfinder;
        std::unique_ptr<WaveManager> m_waveManager;
        
        Player m_player;
        CoreStorage m_cores;

        std::vector<TowerPtr> m_towers;
        std::vector<CreaturePtr> m_creatures;
        std::vector<VFXPtr> m_vfxs;
        Events m_events;

        TowerFactory m_towerFactory;
        CreatureFactory m_creatureFactory;
        VFXFactory m_vfxFactory;
    };

} // namespace tdg::engine

#endif // GAME_HPP
