#include <iostream>
#include <SFML/Graphics.hpp>
#include "infrastructure/tguiManager.hpp"

namespace tdg::infra {
    
    TGUIManager::TGUIManager(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<float> tileSize)
        : m_tileSize(tileSize), m_window(window)
    {
        m_gui = std::make_shared<tgui::Gui>(*window);

        try { m_gui->setFont("../assets/fonts/lexend-black.ttf"); } 
        catch (...) { std::cerr << "Failed to load GUI font.\n"; }

        // Initialize panels
        m_hud = std::make_unique<HUD>();
        m_towerPanel = std::make_unique<TowerPanel>(window, m_tileSize);
        m_mainMenu = std::make_unique<MainMenu>(m_gui, m_onStartStory, m_onStartArcade, m_onQuit);
        m_pauseMenu = std::make_unique<PauseMenu>(m_gui, m_onResume, m_onRestartLevel, m_onMainMenu, m_onQuit);
        m_victoryMenu = std::make_unique<VictoryMenu>(m_gui, m_onNextLevel, m_onRestartLevel, m_onMainMenu, m_onQuit);
        m_gameOverMenu = std::make_unique<GameOverMenu>(m_gui, m_onRestartLevel, m_onMainMenu, m_onQuit);
    }

    void TGUIManager::processEvent(const sf::Event& event) {
        // Transmit event to TGUI
        m_gui->handleEvent(event);


        if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
            if (key->code == sf::Keyboard::Key::Escape) {
                m_onPause(); m_pauseMenu->show();
            }
        }
        // Manage clics
        if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mouse->button == sf::Mouse::Button::Left) {
                // Click on panel first
                if (m_towerPanel->handleClick(mouse->position)) return; // Clic consumed

                // Then, check for tile click
                sf::Vector2f mousePos = m_window->mapPixelToCoords(mouse->position);
                sf::Vector2i tilePos = sf::Vector2i(mousePos.x / *m_tileSize, mousePos.y / *m_tileSize);
                m_towerPanel->handleTileClick(tilePos);
            }
            if (mouse->button == sf::Mouse::Button::Right)
                m_onAccelerate();
        } else if (const auto* mouse = event.getIf<sf::Event::MouseButtonReleased>()) {
            if (mouse->button == sf::Mouse::Button::Right)
                m_onNormalSpeed();
        }

        if (const auto* mouse = event.getIf<sf::Event::MouseMoved>()) {
            sf::Vector2f mousePos = m_window->mapPixelToCoords(mouse->position);
            sf::Vector2i tilePos = sf::Vector2i(mousePos.x / *m_tileSize, mousePos.y / *m_tileSize);
            m_towerPanel->handleMouseMove(tilePos);
        }


    }

    void TGUIManager::showMainMenu() {
        m_mainMenu->show();
    }
    
    void TGUIManager::showHUD() {
        
    }
    
    void TGUIManager::showPauseMenu() {
        m_pauseMenu->show();
    }

    void TGUIManager::showGameOver() {
        m_gameOverMenu->show();
    }

    void TGUIManager::showVictory() {
        m_victoryMenu->show();
    }

    void TGUIManager::update(float dt) {
        m_hud->update(dt);
    }

    void TGUIManager::renderInGUIView(core::IVideoRenderer& vidRenderer, bool showhud) {
        if (showhud) {
            m_hud->draw(vidRenderer);
            m_towerPanel->draw(vidRenderer);
        }
        m_gui->draw();
    }

    void TGUIManager::renderInGameView(core::IVideoRenderer& vidRenderer) {
        m_towerPanel->drawOverlays(vidRenderer);
    }

    void TGUIManager::setGameViewProvider(core::GameViewProvider provider) {
        m_hud->setProvider(std::move(provider));
        m_towerPanel->setProvider(std::move(provider));
    }

    void TGUIManager::setCallbacksFurther() {
        m_towerPanel->onBuildRequest = onBuildRequest;
        m_towerPanel->onUpgradeRequest = onUpgradeRequest;
        m_towerPanel->onSellRequest = onSellRequest;
        m_towerPanel->onTowerRangeRequest = onTowerRangeRequest;
        m_towerPanel->onCanAffordRequest = onCanAffordRequest;
        m_towerPanel->onTileOpenRequest = onTileOpenRequest;
        m_towerPanel->onTowerAtRequest = onTowerAtRequest;
        m_towerPanel->onCostRequest = onCostRequest;
    }

} // namespace tdg::infra
