#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

class Game;
class Renderer;

/**
 * GuiManager
 *
 * Responsibilities:
 * - Create and manage TGUI widgets (pause menu, tower selection menu, error popups).
 * - Provide a small API to be called from the main event loop:
 *      - processEvent(...)  -- pass SFML events here
 *      - handleLeftClick(x,y) -- if the user clicks on the game view
 * - When opening menus it will pause/unpause the game by calling Game::setPaused(bool)
 *   (if you don't have setPaused, GuiManager will rely on caller to pause).
 */
class GuiManager {
private:
    tgui::Gui& gui;
    Game& game;
    Renderer& renderer;

    tgui::Panel::Ptr pausePanel;
    tgui::Panel::Ptr towerMenu;
    tgui::Panel::Ptr errorPanel;

    bool paused = false;

    // helpers
    void openTowerMenuAtTile(const sf::Vector2i& tilePos);
    void closeTowerMenu();
    void openPauseMenu();
    void closePauseMenu();
    void scheduleRemoveWidget(tgui::Widget::Ptr widget, unsigned int ms);

public:
    GuiManager(tgui::Gui& gui, Game& game, Renderer& renderer);

    /// Process an SFML event (forward to TGUI and handle ESC)
    void processEvent(const sf::Event& event);

    /// Handle a left mouse click (in window coordinates); will open tower menu if appropriate
    void handleLeftClick(int mouseX, int mouseY);

    /// Toggle pause menu programmatically
    void togglePause();

    /// Show an error popup (short)
    void showError(const std::string& message);
};

#endif // GUIMANAGER_HPP
