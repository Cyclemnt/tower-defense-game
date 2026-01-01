#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "engine/game.hpp"
#include "core/interfaces/iMapSource.hpp"
#include "core/interfaces/iWaveSource.hpp"

#include "core/interfaces/iVideoRenderer.hpp"
#include "core/interfaces/iAudioRenderer.hpp"

#include "engine/commandBus.hpp"
#include "engine/inputSystem.hpp"
#include "engine/guiManager.hpp"

#include "engine/viewManager.hpp"

namespace tdg::engine {

    class GameManager {
    public:
        enum class State { MainMenu, Loading, Story, Arcade, WaitingForInput };

        GameManager();

        void setState(State state);
        void run();

    private:
        void restartLevel();
        void nextLevel();
        void startStoryMode();
        void startArcadeMode();
        void loadLevel();

        void setGameSpeed(float speed) { m_gameSpeed = speed; }

        void processCommands();

        sf::Clock m_clock;
        std::shared_ptr<sf::RenderWindow> m_window;
        std::unique_ptr<ViewManager> m_viewManager;

        State m_state { State::MainMenu };
        State m_gameMode { State::MainMenu };

        std::unique_ptr<core::IVideoRenderer> m_videoRenderer;
        std::unique_ptr<core::IAudioRenderer> m_audioRenderer;

        std::shared_ptr<CommandBus> m_bus;
        std::unique_ptr<InputSystem> m_inputSystem;
        std::unique_ptr<TGUIManager> m_guiManager;

        std::shared_ptr<Game> m_game;

        std::shared_ptr<core::IMapSource> m_mapSource;
        std::shared_ptr<core::IWaveSource> m_waveSource;

        unsigned int m_waveLevel{1u};
        unsigned int m_mapLevel{1u};
        const unsigned int m_arcadeMapLevel{3u};
        bool m_running{false};
        bool m_pause{false};
        float m_gameSpeed{1.0f};
    };

} // namespace tdg::engine

#endif // GAME_MANAGER_HPP
