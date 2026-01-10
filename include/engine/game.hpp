#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <optional>

#include "iGame.hpp"

#include "core/map.hpp"
#include "core/interfaces/iPathfinder.hpp"
#include "core/waveManager.hpp"

#include "core/player.hpp"
#include "core/coreStorage.hpp"

#include "core/events.hpp"

#include "core/managers/roamingCoreManager.hpp"
#include "core/managers/creatureManager.hpp"
#include "core/managers/towerManager.hpp"
#include "core/managers/vfxManager.hpp"
#include "core/managers/sfxManager.hpp"

#include "core/animationGenerator.hpp"

namespace tdg::core { class IWaveSource; class IMapSource; class IVideoRenderer; class IAudioRenderer; }

namespace tdg::engine {

    using namespace tdg::core;

    class Game final : public IGame {
    public:
        explicit Game(std::shared_ptr<IMapSource> mapSrc, std::shared_ptr<IWaveSource> waveSrc,
            unsigned int startCores = 24u, Materials startMaterials = {30u,50u,150u});

        void update(float dt);
        void renderVideo(IVideoRenderer& renderer) const;
        void renderAudio(IAudioRenderer& audRenderer);

        void generateBackgroundAnimations();

        bool buildTower(std::string towerType, int x, int y);
        bool upgradeTower(int x, int y);
        bool sellTower(int x, int y);

        void spawnCreature(std::string creatureType, unsigned int level, std::optional<unsigned int> entry);

        bool isWaveOver() const;
        bool isGameOver() const;
        bool isVictory() const;

        /* Interface */
        bool tileOpenAt(int x, int y) const override;
        bool towerAt(int x, int y) const override;
        std::optional<float> towerRangeAt(int x, int y) const override;
        std::optional<Materials> towerCost(std::string towerType) const override;
        bool canAfford(std::string towerType) const override;

        Materials playerBalance() const noexcept override;
        CoresState coresState() const noexcept override;
        WaveState waveState() const noexcept override;

        int mapWidth() const override { return m_map->width(); }
        int mapHeight() const override { return m_map->height(); }
        /* ========= */

    private:        
        unsigned long m_tick{0u};
        bool m_over{false};
        
        std::unique_ptr<Map> m_map;
        std::unique_ptr<IPathfinder> m_pathfinder;
        std::unique_ptr<WaveManager> m_waveManager;
        
        Player m_player;
        CoreStorage m_cores;

        Events m_events;

        RoamingCoreManager m_roamingCoreManager;
        CreatureManager m_creatureManager;
        TowerManager m_towerManager;
        VFXManager m_vfxManager;
        SFXManager m_sfxManager;

        AnimationGenerator m_animation;
    };

} // namespace tdg::engine

#endif // GAME_HPP
