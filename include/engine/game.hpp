#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <optional>

#include "core/map.hpp"
#include "core/interfaces/iPathfinder.hpp"
#include "core/waveManager.hpp"

#include "core/player.hpp"
#include "core/coreStorage.hpp"

#include "core/events.hpp"

#include "core/gameViewProvider.hpp"

#include "core/managers/towerManager.hpp"
#include "core/managers/creatureManager.hpp"
#include "core/managers/vfxManager.hpp"
#include "core/managers/sfxManager.hpp"

namespace tdg::core { class IWaveSource; class IMapSource; class IVideoRenderer; class IAudioRenderer; }

namespace tdg::engine {

    using namespace tdg::core;

    class Game final {
    public:
        explicit Game(std::shared_ptr<IMapSource> mapSrc, std::shared_ptr<IWaveSource> waveSrc,
            unsigned int startCores = 24u, Materials startMaterials = {30u,50u,150u});

        void update(float dt);
        void renderVideo(IVideoRenderer& renderer) const;
        void renderAudio(IAudioRenderer& audRenderer);

        bool buildTower(std::string towerType, int x, int y);
        bool upgradeTower(int x, int y);
        bool sellTower(int x, int y);

        void spawnCreature(std::string creatureType, unsigned int level, std::optional<unsigned int> entry);

        GameView getView() const; // Gives global information about the state of the game (useful for HUD)

        bool isWaveOver() const;
        bool isGameOver() const;
        bool isVictory() const;

        /* Some useful getters for GUI */
        bool tileOpenAt(int x, int y) const;
        bool towerAt(int x, int y) const;
        std::optional<float> towerRangeAt(int x, int y) const;
        std::optional<Materials> towerCost(std::string towerType) const;
        bool canAfford(std::string towerType) const;

        int mapWidth() const { return m_map->width(); }
        int mapHeight() const { return m_map->height(); }
        /* =========================== */

    private:        
        unsigned long m_tick{0u};
        
        std::unique_ptr<Map> m_map;
        std::unique_ptr<IPathfinder> m_pathfinder;
        std::unique_ptr<WaveManager> m_waveManager;
        
        Player m_player;
        CoreStorage m_cores;

        Events m_events;

        TowerManager m_towerManager;
        CreatureManager m_creatureManager;
        VFXManager m_vfxManager;
        SFXManager m_sfxManager;
    };

} // namespace tdg::engine

#endif // GAME_HPP
