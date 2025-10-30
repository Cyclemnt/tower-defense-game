#ifndef GUI_MANAGER_HPP
#define GUI_MANAGER_HPP

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include "pauseMenu.hpp"
#include "towerPanel.hpp"
#include "hud.hpp"
#include "cameraController.hpp"
#include "../game.hpp"
#include "../renderer/renderContext.hpp"

/**
 * @class GuiManager
 * @brief Manages all GUI elements and interactions.
 *
 * Handles user input (clicks, zoom, drag), opens menus, and renders HUD.
 * The GuiManager acts as a bridge between TGUI widgets and the in-game world.
 */
class GuiManager final {
private:
    tgui::Gui gui;            ///< Root GUI container
    const RenderContext& ctx; ///< Read-only rendering context
    Game& game;               ///< Reference to the main game instance
    HUD hud;                  ///< Heads-up display (resources, cores, FPS)
    CameraController camera;  ///< Handles camera movement
    PauseMenu pauseMenu;      ///< In-game pause menu
    TowerPanel towerPanel;    ///< Tower building/selling panel

public:
    GuiManager(sf::RenderWindow& window, Game& game_, RenderContext& ctx_);

    /// @brief Processes SFML events (keyboard, mouse, etc.).
    void processEvent(const sf::Event& event);

    /// @brief Draws the HUD and GUI overlays.
    void draw(float deltaTime);
};

#endif // GUI_MANAGER_HPP
