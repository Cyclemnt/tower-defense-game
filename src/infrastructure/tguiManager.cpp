#include <iostream>
#include "infrastructure/tguiManager.hpp"

namespace tdg::infra {
    
    TGUIManager::TGUIManager(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<float> tileSize)
        : m_tileSize(tileSize)
    {
        m_gui = std::make_shared<tgui::Gui>(*window);
        
        try { m_gui->setFont("../assets/fonts/lexend-black.ttf"); } 
        catch (...) { std::cerr << "Failed to load GUI font.\n"; }

        // Initialize panels
        m_hud = std::make_unique<HUD>();
        m_mainMenu = std::make_unique<MainMenu>(m_gui, m_onStartStory, m_onStartArcade, m_onQuit);
        m_pauseMenu = std::make_unique<PauseMenu>(m_gui, m_onResume, m_onRestartLevel, m_onMainMenu, m_onQuit);
        m_victoryMenu = std::make_unique<VictoryMenu>(m_gui, m_onNextLevel, m_onRestartLevel, m_onMainMenu, m_onQuit);
        m_gameOverMenu = std::make_unique<GameOverMenu>(m_gui, m_onRestartLevel, m_onMainMenu, m_onQuit);
    }

    void TGUIManager::processEvent(const sf::Event& event) {
        // Transmit event to TGUI
        m_gui->handleEvent(event);
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

    void TGUIManager::render(core::IVideoRenderer& vidRenderer) {
        m_hud->draw(vidRenderer);
        m_gui->draw();
    }

    void TGUIManager::setHUDProvider(core::HUDProvider provider) {
        m_hud->setProvider(std::move(provider));
    }

} // namespace tdg::infra
