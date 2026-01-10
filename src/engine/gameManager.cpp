#include "engine/gameManager.hpp"
#include "infrastructure/fileMapSource.hpp"
#include "infrastructure/autoWaveSource.hpp"
#include "infrastructure/jsonWaveSource.hpp"

#include "infrastructure/sfmlResourceManager.hpp"
#include "infrastructure/sfmlVideoRenderer.hpp"
#include "infrastructure/sfmlAudioRenderer.hpp"
#include "engine/guiManager.hpp"

#include <iostream>

namespace tdg::engine {
    
    GameManager::GameManager() {
        // Game data sources
        m_mapSource = std::make_shared<infra::FileMapSource>("../assets/maps/");
        m_waveSource = std::make_shared<infra::JsonWaveSource>("../assets/waves/");

        // Window
        m_window = std::make_shared<sf::RenderWindow>();
        m_window->create(sf::VideoMode::getDesktopMode(), "Tower Defense Game", sf::State::Fullscreen);
        m_window->setFramerateLimit(60);

        // Ressources for the renderers
        std::shared_ptr<infra::SFMLResourceManager> ressources = std::make_shared<infra::SFMLResourceManager>();
        std::shared_ptr<float> tileSize = std::make_shared<float>(64.0f);

        // SFML View Manager
        m_viewManager = std::make_unique<ViewManager>(m_window, tileSize);

        // Renderers
        m_videoRenderer = std::make_unique<infra::SFMLVideoRenderer>(m_window, ressources, tileSize);
        m_audioRenderer = std::make_unique<infra::SFMLAudioRenderer>(ressources);

        // Command bus, input system and GUI
        m_bus = std::make_shared<CommandBus>();
        m_inputSystem = std::make_unique<InputSystem>(m_bus);
        m_guiManager = std::make_unique<TGUIManager>(m_window, tileSize, m_bus);

        // Launching
        setState(State::MainMenu);
    }

    void GameManager::setState(State state) {
        m_running = false;

        switch (state) {
            case State::MainMenu:
                m_guiManager->showMainMenu();
                m_state = State::WaitingForInput;
                break;
            
            case State::Story:
                m_state = State::Loading;
                startStoryMode();
                m_gameMode = m_state = State::Story;
                break;
                
            case State::Arcade:
                m_state = State::Loading;
                startArcadeMode();
                m_gameMode = m_state = State::Arcade;
                break;

            default: break;
        }
        
        run(); // should be at the end of startXMode(), probably
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
                m_inputSystem->processEvent(*event);
                m_guiManager->processEvent(*event);
                processCommands();
            }

            m_audioRenderer->setPitch(m_gameSpeed);

            // Update
            float dt = m_clock.restart().asSeconds();
            if (m_game) m_game->update(dt * m_gameSpeed * !m_pause);
            m_guiManager->update(dt);

            // Render
            m_window->clear();
            m_videoRenderer->setWorldCoordinates(true);
            if (m_game) m_game->renderVideo(*m_videoRenderer);
            if (m_game) m_game->renderAudio(*m_audioRenderer);
            m_videoRenderer->setWorldCoordinates(false);
            
            m_guiManager->renderInGameView(*m_videoRenderer);
            
            m_viewManager->setView(ViewManager::View::GUI);
            m_guiManager->renderInGUIView(*m_videoRenderer, m_state != State::WaitingForInput);
            m_viewManager->setView(ViewManager::View::Game);

            m_window->display();

            // Check for level end
            if (m_state != State::WaitingForInput) if (m_game->isGameOver()) { m_guiManager->showGameOver(); m_state = State::WaitingForInput; }
            if (m_state != State::WaitingForInput) if (m_game->isVictory()) { m_guiManager->showVictory(); m_state = State::WaitingForInput; }
        }
    }

    void GameManager::restartLevel() {
        loadLevel();
        m_state = m_gameMode;
        m_pause = false;
        run();
    }

    void GameManager::nextLevel() {
        if (m_mapLevel >= 5u) m_window->close(); // Lazy
        m_waveLevel++;
        if (m_gameMode == State::Story) m_mapLevel++;
        loadLevel();
        m_state = m_gameMode;
        m_pause = false;
        run();
    }

    void GameManager::startStoryMode() {
        m_waveSource = std::make_shared<infra::JsonWaveSource>("../assets/waves/");
        m_waveLevel = m_mapLevel = 1u;
        loadLevel();
        m_pause = false;
    }

    void GameManager::startArcadeMode() {
        m_waveSource = std::make_shared<infra::AutoWaveSource>();
        m_waveLevel = 0u; m_mapLevel = 3u;
        loadLevel();
        m_pause = false;
    }

    void GameManager::loadLevel() {
        m_mapSource->setLevel(m_mapLevel);
        m_waveSource->setLevel(m_waveLevel);
        m_game = std::make_unique<Game>(m_mapSource, m_waveSource);
        m_guiManager->setGamePtr(m_game);
        m_viewManager->resetGameView(m_game->mapWidth(), m_game->mapHeight());
    }

    void GameManager::processCommands() {
        while (!m_bus->empty()) {
            Command c = m_bus->pop();
            switch (c.type) {
                case Command::Type::Build: {
                    if (auto p = std::get_if<BuildPayload>(&c.payload.value())) {
                        if (m_game) m_game->buildTower(p->towerType, p->tx, p->ty);
                    }
                    break;
                }

                case Command::Type::Upgrade: {
                    if (auto p = std::get_if<UpgradePayload>(&c.payload.value())) {
                        if (m_game) m_game->upgradeTower(p->tx, p->ty);
                    }
                    break;
                }

                case Command::Type::Sell: {
                    if (auto p = std::get_if<SellPayload>(&c.payload.value())) {
                        if (m_game) m_game->sellTower(p->tx, p->ty);
                    }
                    break;
                }

                case Command::Type::TogglePause: {
                    m_pause = !m_pause;
                    m_guiManager->setPauseMenu(m_pause);
                    break;
                }

                case Command::Type::setSpeed: {
                    if (auto p = std::get_if<setGameSpeedPayload>(&c.payload.value())) {
                        setGameSpeed(p->speed);
                    }
                    break;
                }

                case Command::Type::ResetView: {
                    if (m_game) m_viewManager->resetGameView(m_game->mapWidth(), m_game->mapHeight());
                    break;
                }

                case Command::Type::PanView: {
                    if (auto p = std::get_if<PanViewPayload>(&c.payload.value())) {
                        m_viewManager->panGameView(p->delta);
                    }
                    break;
                }

                case Command::Type::ZoomView: {
                    if (auto p = std::get_if<ZoomViewPayload>(&c.payload.value())) {
                        m_viewManager->zoomGameView(p->factor, p->focus);
                    }
                    break;
                }

                case Command::Type::LeftClick: {
                    if (auto p = std::get_if<LeftClickPayload>(&c.payload.value())) {
                        m_guiManager->handleLeftClick(p->pixel);
                    }
                    break;
                }

                case Command::Type::MouseMoved: {
                    if (auto p = std::get_if<MouseMovedPayload>(&c.payload.value())) {
                        m_guiManager->handleMouseMove(p->pixel);
                    }
                    break;
                }

                case Command::Type::RestartLevel: { restartLevel(); break; }
                case Command::Type::NextLevel: { nextLevel(); break; }
                case Command::Type::Quit: { m_window->close(); break; }
                case Command::Type::MainMenu: { setState(State::MainMenu); break; }
                case Command::Type::StartStory: { setState(State::Story); break; }
                case Command::Type::StartArcade: { setState(State::Arcade); break; }

                default: break;
            }
        }
    }

} // namespace tdg::engine
