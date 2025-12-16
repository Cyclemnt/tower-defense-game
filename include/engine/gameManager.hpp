#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "engine/game.hpp"
#include "core/interfaces/iMapSource.hpp"
#include "core/interfaces/iWaveSource.hpp"

#include "core/interfaces/iVideoRenderer.hpp"
#include "core/interfaces/iAudioRenderer.hpp"
#include "core/interfaces/iGuiManager.hpp"

namespace tdg::engine {

    class GameManager {
    public:
        enum class State { MainMenu, Loading, Story, Arcade, Victory, GameOver, WaitingForUserInput };

        GameManager();

        void setState(State state);
        void run();

    private:
        void restartLevel();
        void nextLevel();
        void startStoryMode();
        void startArcadeMode();
        void loadLevel();

        std::shared_ptr<sf::RenderWindow> m_window;
        sf::Clock m_clock;

        State m_state { State::MainMenu };
        State m_previousState { State::MainMenu };
        std::unique_ptr<core::IVideoRenderer> m_videoRenderer;
        std::unique_ptr<core::IAudioRenderer> m_audioRenderer;
        std::unique_ptr<core::IGUIManager> m_guiManager;
        std::unique_ptr<Game> m_game;

        std::shared_ptr<core::IMapSource> m_mapSource;
        std::shared_ptr<core::IWaveSource> m_waveSource;

        unsigned int m_waveLevel{1u};
        unsigned int m_mapLevel{1u};
        const unsigned int m_arcadeMapLevel{3u};
        bool m_running{false};
        bool m_pause{false};
        float m_acceleration{1.0f};
    };

} // namespace tdg::engine

#endif // GAME_MANAGER_HPP
