#include "engine/gameManager.hpp"
#include "infrastructure/fileMapSource.hpp"
#include "infrastructure/autoWaveSource.hpp"
#include "infrastructure/jsonWaveSource.hpp"

#include "infrastructure/sfmlResourceManager.hpp"
#include "infrastructure/sfmlVideoRenderer.hpp"
#include "infrastructure/sfmlAudioRenderer.hpp"
#include "infrastructure/tguiManager.hpp"

namespace tdg::engine {
    
    GameManager::GameManager() {
        m_mapSource = std::make_shared<infra::FileMapSource>("../assets/maps/");
        m_waveSource = std::make_shared<infra::JsonWaveSource>("../assets/waves/");

        m_window = std::make_shared<sf::RenderWindow>();
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        m_window->create(desktop, "Tower Defense Game", sf::State::Fullscreen);
        m_window->setFramerateLimit(60);
        auto ressources = std::make_shared<infra::SFMLResourceManager>();
        auto tileSize = std::make_shared<float>(100.0f);

        m_videoRenderer = std::make_unique<infra::SFMLVideoRenderer>(m_window, ressources, tileSize);
        m_audioRenderer = std::make_unique<infra::SFMLAudioRenderer>(ressources);
        m_gui = std::make_unique<infra::TGUIManager>(m_window, tileSize);
    }

    void GameManager::setState(State state) {
        m_running = false;

        switch (state) {
        case State::MainMenu:
            /* code */
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
            
        case State::Pause:
            m_state = State::Pause;
            break;
        
        case State::Resume:
            m_running = true;
            m_state = State::Pause;
            break;

        case State::Victory:
            /* code */
            break;

        case State::GameOver:
            /* code */
            break;

        default:
            break;
        }
    }

    void GameManager::run() {
        m_running = true;
        
        while (m_window->isOpen() && m_running) {
            // --- Events ---
            while (auto event = m_window->pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    m_window->close();
                    return;
                }
                // guiManager->processEvent(*event);
            }

            // --- Update ---
            float dt = m_clock.restart().asSeconds();
            m_game->update(dt);

            // --- Render ---
            m_window->clear();
            m_game->render(*m_videoRenderer);
            m_window->display();
        }
    }

    void GameManager::startStoryMode() {
        m_waveSource = std::make_shared<infra::JsonWaveSource>("../assets/waves/");
        m_level = 1u;
        loadLevel(m_level, m_level);
    }

    void GameManager::startArcadeMode() {
        m_waveSource = std::make_shared<infra::AutoWaveSource>();
        m_level = 1u;
        loadLevel(m_arcadeMapLevel, m_level);
    }

    void GameManager::loadLevel(unsigned int maplvl, unsigned int wavlvl) {
        m_mapSource->setLevel(maplvl);
        m_waveSource->setLevel(wavlvl);
        m_game = std::make_unique<Game>(m_mapSource, m_waveSource);
    }

} // namespace tdg::engine
