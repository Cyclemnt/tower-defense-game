#include "engine/gameManager.hpp"
#include "infrastructure/fileMapSource.hpp"
#include "infrastructure/autoWaveSource.hpp"
#include "infrastructure/jsonWaveSource.hpp"

#include "infrastructure/sfmlResourceManager.hpp"
#include "infrastructure/sfmlVideoRenderer.hpp"
#include "infrastructure/sfmlAudioRenderer.hpp"
#include "infrastructure/tguiManager.hpp"
// #include "infrastructure/sfmlInputController.hpp"
#include <iostream>
namespace tdg::engine {
    
    GameManager::GameManager() {
        // Game data sources
        m_mapSource = std::make_shared<infra::FileMapSource>("../assets/maps/");
        m_waveSource = std::make_shared<infra::JsonWaveSource>("../assets/waves/");

        // Data for Renderers and GUI
        m_window = std::make_shared<sf::RenderWindow>();
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        m_window->create(desktop, "Tower Defense Game", sf::State::Fullscreen);
        m_window->setFramerateLimit(60);
        auto ressources = std::make_shared<infra::SFMLResourceManager>();
        auto tileSize = std::make_shared<float>(64.0f);

        // Renderers and GUI
        m_videoRenderer = std::make_unique<infra::SFMLVideoRenderer>(m_window, ressources, tileSize);
        m_audioRenderer = std::make_unique<infra::SFMLAudioRenderer>(ressources);
        m_guiManager = std::make_unique<infra::TGUIManager>(m_window, tileSize);

        // Set GUI Callbacks
        m_guiManager->m_onPause = [this](){ m_pause = true; };
        m_guiManager->m_onResume = [this](){ m_pause = false; };
        m_guiManager->m_onRestartLevel = [this]() { loadLevel(); };
        m_guiManager->m_onQuit = [this](){ m_window->close(); };
        m_guiManager->m_onMainMenu = [this](){ setState(State::MainMenu); };
        m_guiManager->m_onStartStory = [this]() { setState(State::Story); };
        m_guiManager->m_onStartArcade = [this]() { setState(State::Arcade); };
        m_guiManager->m_onNextLevel = [this]() { nextLevel(); };

        m_guiManager->setHUDProvider([this]() -> std::optional<core::HUDState> {
            if (!m_game) return std::nullopt;
            return m_game->getView();
        });

        // Launching
        setState(State::MainMenu);
    }

    void GameManager::setState(State state) {
        m_running = false;

        switch (state) {
        case State::MainMenu:
            m_guiManager->showMainMenu();
            m_state = State::WaitingForUserInput;
            run();
            break;
        
        case State::Story:
            m_state = State::Loading;
            startStoryMode();
            m_state = State::Story;
            run();
            break;
            
        case State::Arcade:
            m_state = State::Loading;
            startArcadeMode();
            m_state = State::Arcade;
            run();
            break;

        case State::Victory:
            m_guiManager->showVictory();
            m_state = State::WaitingForUserInput;
            break;

        case State::GameOver:
            m_guiManager->showGameOver();
            m_state = State::WaitingForUserInput;
            break;

        default:
            break;
        }
    }

    void GameManager::run() {
        m_running = true;

        while (m_window->isOpen() && m_running) {
            // Events
            while (auto event = m_window->pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    m_window->close();
                    return;
                }
                m_guiManager->processEvent(*event);
            }

            // Update
            float dt = m_clock.restart().asSeconds();
            if (m_state != State::WaitingForUserInput) if (!m_pause) m_game->update(dt);
            m_guiManager->update(dt);

            // Render
            m_window->clear();
            if (m_state != State::WaitingForUserInput) m_game->renderVideo(*m_videoRenderer);
            if (m_state != State::WaitingForUserInput) m_game->renderAudio(*m_audioRenderer);
            m_guiManager->render(*m_videoRenderer);
            m_window->display();

            if (m_state != State::WaitingForUserInput) if (m_game->isGameOver()) setState(State::GameOver);
            if (m_state != State::WaitingForUserInput) if (m_game->isVictory()) setState(State::Victory);
        }
    }

    void GameManager::nextLevel() {
        m_waveLevel++;
        if (m_state == State::Story) m_mapLevel++;
    }

    void GameManager::startStoryMode() {
        m_waveSource = std::make_shared<infra::JsonWaveSource>("../assets/waves/");
        m_waveLevel = m_mapLevel = 1u;
        loadLevel();
    }

    void GameManager::startArcadeMode() {
        m_waveSource = std::make_shared<infra::AutoWaveSource>();
        m_waveLevel = 1u; m_mapLevel = 3u;
        loadLevel();
    }

    void GameManager::loadLevel() {
        m_mapSource->setLevel(m_mapLevel);
        m_waveSource->setLevel(m_waveLevel);
        m_game = std::make_unique<Game>(m_mapSource, m_waveSource);
    }

} // namespace tdg::engine
