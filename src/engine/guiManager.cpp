#include <iostream>
#include <SFML/Graphics.hpp>
#include "engine/guiManager.hpp"

namespace tdg::engine {
    
    TGUIManager::TGUIManager(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<float> tileSize, std::shared_ptr<engine::CommandBus> bus)
        : m_tileSize(tileSize), m_window(window), m_bus(bus)
    {
        m_gui = std::make_shared<tgui::Gui>(*window);

        try { m_gui->setFont("../assets/fonts/lexend-black.ttf"); } 
        catch (...) { std::cerr << "Failed to load GUI font.\n"; }

        // Initialize panels
        m_hud = std::make_unique<HUD>(m_window);
        m_towerPanel = std::make_unique<TowerPanel>(m_window, m_tileSize, m_bus);
        m_mainMenu = std::make_unique<MainMenu>(m_gui, m_bus);
        m_pauseMenu = std::make_unique<PauseMenu>(m_gui, m_bus);
        m_victoryMenu = std::make_unique<VictoryMenu>(m_gui, m_bus);
        m_gameOverMenu = std::make_unique<GameOverMenu>(m_gui, m_bus);
    }

    void TGUIManager::processEvent(const sf::Event& event) {
        m_gui->handleEvent(event);
    }
    
    void TGUIManager::handleLeftClick(sf::Vector2i pixel) {
        m_towerPanel->handleClick(pixel);
        sf::Vector2i tilePos = sf::Vector2i(m_window->mapPixelToCoords(pixel) / *m_tileSize);
        m_towerPanel->handleTileClick(tilePos);
    }

    void TGUIManager::handleMouseMove(sf::Vector2i pixel) {
        sf::Vector2i tilePos = sf::Vector2i(m_window->mapPixelToCoords(pixel) / *m_tileSize);
        m_towerPanel->handleMouseMove(tilePos);
    }

    void TGUIManager::showMainMenu() {
        m_mainMenu->show();
    }
    
    void TGUIManager::setPauseMenu(bool show) {
        if (show) m_pauseMenu->show();
        else m_pauseMenu->close();
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

    void TGUIManager::setGamePtr(std::weak_ptr<IGame> game) {
        m_hud->setGamePtr(game);
        m_towerPanel->setGamePtr(game);
    }

} // namespace tdg::engine
