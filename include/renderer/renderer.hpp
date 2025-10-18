#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <string>
#include "game.hpp"
#include "renderer/renderContext.hpp"

/**
 * @class Renderer
 * @brief Handles all rendering and user interface interactions.
 *
 * The Renderer draws the map, creatures, and towers using textures.
 * It also manages the TGUI menus for tower selection and pause.
 */
class Renderer {
private:
    tgui::Gui& gui;     ///< GUI manager (TGUI)
    RenderContext ctx;  ///< Render context to give to every drawn entity

    bool paused = false; ///< flag for the state of the game (pause/play)

    /// @brief Cache of textures to avoid reloading from disk
    std::unordered_map<std::string, sf::Texture> textures;

    // GUI panels
    tgui::Panel::Ptr pausePanel;
    tgui::Panel::Ptr towerMenu;

    /// @brief Convert pixel coordinates to tile coordinates.
    sf::Vector2i screenToTile(int mouseX, int mouseY) const;

public:
    Renderer(sf::RenderWindow& win, tgui::Gui& g);

    const sf::Texture& getTexture(const std::string& name);

    void computeScaling(const Game& game);

    /// @brief Draws the full game scene.
    void render(const Game& game);

    void highlightTile(const Game& game);

    /// @brief Draws the HUD.
    void drawHUD(const Game& game);

    /// @brief Handles left mouse click to open the tower selection menu.
    void handleMouseClick(int mouseX, int mouseY, Game& game);

    /// @brief Opens a menu to choose which tower to place.
    void openTowerMenu(sf::Vector2i tilePos, Game& game);

    /// @brief Toggles the pause menu on/off.
    void togglePauseMenu(bool isPaused, Game& game);

    /// @brief Shows an error message popup.
    void showError(const std::string& msg);
};

#endif // RENDERER_HPP
