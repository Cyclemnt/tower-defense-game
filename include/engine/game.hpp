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

#include "core/gameViewProvider.hpp"

#include "core/towers/tower.hpp"
#include "core/creatures/creature.hpp"
#include "core/vfxs/vfx.hpp"
#include "core/events.hpp"

#include "core/factories/towerFactory.hpp"
#include "core/factories/creatureFactory.hpp"
#include "core/factories/vfxFactory.hpp"

#include "core/interfaces/iVideoRenderer.hpp"
#include "core/interfaces/iAudioRenderer.hpp"

namespace tdg::core { class IWaveSource; class IMapSource; }

namespace tdg::engine {

    using namespace tdg::core;

    class Game {
    public:
        explicit Game(std::shared_ptr<IMapSource> mapSrc, std::shared_ptr<IWaveSource> waveSrc,
            unsigned int startCores = 24u, Materials startMaterials = {100u,100u,100u});

        void update(float dt);
        void renderVideo(IVideoRenderer& renderer) const;
        void renderAudio(IAudioRenderer& audRenderer);

        bool buildTower(Tower::Type type, int x, int y);
        bool upgradeTower(int x, int y);
        bool sellTower(int x, int y);

        void spawnCreature(Creature::Type type, unsigned int level, std::optional<unsigned int> entry);

        GameView getView() const;

        bool isWaveOver() const;
        bool isGameOver() const;
        bool isVictory() const;

        /* Lack of time (bad time management) made me do that */
        void buildTower(std::string towerType, int x, int y);
        bool canAfford(std::string towerType) const;
        bool canAfford(Tower::Type type) const;
        std::optional<float> towerRangeAt(int x, int y) const;
        bool tileOpenAt(int x, int y) const;
        bool towerAt(int x, int y) const;
        std::optional<Materials> towerCost(std::string towerType) const;
        std::optional<Materials> towerCost(Tower::Type type) const;
        int mapWidth() const { return m_map->width(); }
        int mapHeight() const { return m_map->height(); }
        /* ================================================== */

    private:
        void handlePathEvent();
        void handleDeadCreatures();
        void handleDeadVFX();
        void updatePaths();
        
        unsigned long m_tick{0u};
        
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
