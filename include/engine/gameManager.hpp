#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <memory>
#include "game.hpp"

namespace tdg::infra { class IGui; class IRenderer; }

namespace tdg::engine {

    class GameManager {
    public:
        enum class State { MainMenu, Loading, Playing, Paused, Victory, GameOver };

        GameManager(std::unique_ptr<tdg::infra::IRenderer> renderer,
        std::unique_ptr<tdg::infra::IGui> gui,
        std::shared_ptr<tdg::core::IPathfinder> pathfinder);

        void run();

        void startStoryMode(const std::string& mapFile, const std::string& waveFile);
        void startArcadeMode(const std::string& mapFile);

        void setGame(std::unique_ptr<Game> game);

    private:
        void loadLevel(std::unique_ptr<core::IMapSource> mapSrc,
                       std::unique_ptr<core::IWaveSource> waveSrc);

        State m_state { State::MainMenu };
        std::unique_ptr<tdg::infra::IRenderer> m_renderer;
        std::unique_ptr<tdg::infra::IGui> m_gui;
        std::shared_ptr<tdg::core::IPathfinder> m_pathfinder;
        std::unique_ptr<Game> m_game;

        bool m_running{false};
    };

} // namespace tdg::engine

#endif // GAME_MANAGER_HPP
