#include "engine/gameManager.hpp"
#include "infrastructure/fileMapSource.hpp"
#include "infrastructure/autoWaveSource.hpp"
#include "infrastructure/jsonWaveSource.hpp"

#include "infrastructure/sfmlResourceManager.hpp"
#include "infrastructure/sfmlVideoRenderer.hpp"
#include "infrastructure/sfmlAudioRenderer.hpp"
#include "infrastructure/tguiManager.hpp"

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
        m_tileSize = std::make_shared<float>(64.0f);

        // Renderers and GUI
        m_videoRenderer = std::make_unique<infra::SFMLVideoRenderer>(m_window, ressources, m_tileSize);
        m_audioRenderer = std::make_unique<infra::SFMLAudioRenderer>(ressources);
        m_guiManager = std::make_unique<infra::TGUIManager>(m_window, m_tileSize);

        // Set GUI Callbacks
        m_guiManager->m_onAccelerate = [this](){ accelerate(); };
        m_guiManager->m_onNormalSpeed = [this](){ normalSpeed(); };

        m_guiManager->m_onPause = [this](){ m_pause = true; };
        m_guiManager->m_onResume = [this](){ m_pause = false; };
        m_guiManager->m_onRestartLevel = [this]() { restartLevel(); };
        m_guiManager->m_onQuit = [this](){ m_window->close(); };
        m_guiManager->m_onMainMenu = [this](){ setState(State::MainMenu); };
        m_guiManager->m_onStartStory = [this]() { setState(State::Story); };
        m_guiManager->m_onStartArcade = [this]() { setState(State::Arcade); };
        m_guiManager->m_onNextLevel = [this]() { nextLevel(); };

        /* Please forgive me for these shortcuts */
        m_guiManager->onBuildRequest = [this](std::string towerType, int tx, int ty){ if (m_game) m_game->buildTower(towerType,tx,ty); };
        m_guiManager->onUpgradeRequest = [this](int tx, int ty){ if (m_game) m_game->upgradeTower(tx,ty); };
        m_guiManager->onSellRequest = [this](int tx, int ty){ if (m_game) m_game->sellTower(tx,ty); };
        
        m_guiManager->onTowerRangeRequest = [this](int tx, int ty){ return m_game ? m_game->towerRangeAt(tx,ty) : std::nullopt; };
        m_guiManager->onTowerAtRequest = [this](int tx, int ty){ return m_game ? m_game->towerAt(tx,ty) : false; };
        m_guiManager->onTileOpenRequest = [this](int tx, int ty){ return m_game ? m_game->tileOpenAt(tx,ty) : false; };
        m_guiManager->onCanAffordRequest = [this](std::string towerType){ return m_game ? m_game->canAfford(towerType) : false; };
        m_guiManager->onCostRequest = [this](std::string towerType){ return m_game ? m_game->towerCost(towerType) : std::nullopt; };
        m_guiManager->setCallbacksFurther();
        /* ==================================== */

        m_guiManager->setGameViewProvider([this]() -> std::optional<core::GameView> {
            if (!m_game) return std::nullopt;
            return m_game->getView();
        });

        m_guiView = sf::View(sf::FloatRect({0.0f, 0.0f}, {static_cast<sf::Vector2f>(m_window->getSize())}));
        resetGameView();

        // Launching
        setState(State::MainMenu);
    }

    void GameManager::setState(State state) {
        m_previousState = m_state;
        m_running = false;

        switch (state) {
        case State::MainMenu:
            m_videoRenderer->drawSprite("main_menu", 0, (m_window->getSize().y - 1190.0f) * 0.5f / *m_tileSize, 30);
            m_guiManager->showMainMenu();
            m_state = State::WaitingForUserInput;
            run();
            break;
        
        case State::Story:
            m_state = State::Loading;
            startStoryMode();
            resetGameView();
            m_state = State::Story;
            run();
            break;
            
        case State::Arcade:
            m_state = State::Loading;
            startArcadeMode();
            resetGameView();
            m_state = State::Arcade;
            run();
            break;

        case State::Victory:
            m_guiManager->showVictory();
            m_state = State::WaitingForUserInput;
            run();
            break;

        case State::GameOver:
            m_guiManager->showGameOver();
            m_state = State::WaitingForUserInput;
            run();
            break;

        default:
            break;
        }
    }

    void GameManager::resetGameView() {
        if (!m_game) return;

        const sf::Vector2i mapSize = { m_game->mapWidth(), m_game->mapHeight() };
        sf::Vector2f winSize = static_cast<sf::Vector2f>(m_window->getSize());

        float maxTileSizeX = winSize.x / (mapSize.x + 2);
        float maxTileSizeY = winSize.y / (mapSize.y + 2);
        float newTileSize = std::min(maxTileSizeX, maxTileSizeY);
        
        *m_tileSize = newTileSize;

        // Center the map inside the window
        sf::Vector2f mapSizePx = static_cast<sf::Vector2f>(mapSize) * *m_tileSize;
        sf::Vector2f offset = (static_cast<sf::Vector2f>(winSize) - mapSizePx) * 0.5f;

        // Adjust SFML view
        m_gameView = sf::View(sf::FloatRect({0.0f, 0.0f}, {winSize.x, winSize.y}));
        m_gameView.setCenter(mapSizePx * 0.5f);
    }

    void GameManager::run() {
        m_running = true;
resetGameView();
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
            if (m_state != State::WaitingForUserInput) if (!m_pause) m_game->update(dt * m_acceleration);
            m_guiManager->update(dt);

            // Render
            if (m_state != State::WaitingForUserInput) m_window->clear();
            m_videoRenderer->setWorldCoordinates(true);
            if (m_state != State::WaitingForUserInput) m_game->renderVideo(*m_videoRenderer);
            if (m_state != State::WaitingForUserInput) m_game->renderAudio(*m_audioRenderer);
            m_videoRenderer->setWorldCoordinates(false);
            m_guiManager->renderInGameView(*m_videoRenderer);
            m_window->setView(m_guiView);
            m_guiManager->renderInGUIView(*m_videoRenderer, m_state != State::WaitingForUserInput);
            m_window->display();
            m_window->setView(m_gameView);

            if (m_state != State::WaitingForUserInput) if (m_game->isGameOver()) setState(State::GameOver);
            if (m_state != State::WaitingForUserInput) if (m_game->isVictory()) setState(State::Victory);
        }
    }

    void GameManager::restartLevel() {
        loadLevel();
        // m_state = m_previousState;
        run();
    }

    void GameManager::nextLevel() {
        m_waveLevel++;
        if (m_previousState == State::Story) m_mapLevel++;
        loadLevel();
        m_state = m_previousState;
        run();
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
