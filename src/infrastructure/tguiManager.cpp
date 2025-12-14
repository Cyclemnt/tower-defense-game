#include <iostream>
#include "infrastructure/tguiManager.hpp"

namespace tdg::infra {
    
    TGUIManager::TGUIManager(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<float> tileSize)
        : m_window(window), m_tileSize(tileSize)
    {
        m_gui = std::make_unique<tgui::Gui>(*window);
        
        try { m_gui->setFont("../assets/fonts/lexend-black.ttf"); } 
        catch (...) { std::cerr << "Failed to load GUI font.\n"; }
    }

    void infra::TGUIManager::showMainMenu() {
        
    }
    
    void infra::TGUIManager::showHUD() {
        
    }
    
    void infra::TGUIManager::showPauseMenu() {
        
    }

    void infra::TGUIManager::showGameOver() {
    
    }

    void infra::TGUIManager::showVictory() {
    }

    void infra::TGUIManager::update(float dt) {
    }

    void infra::TGUIManager::render() {
    }

} // namespace tdg::infra
