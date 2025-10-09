#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <unordered_map>
#include <string>
#include "game.hpp"

/**
 * @class Renderer
 * @brief Handles all rendering and user interface interactions.
 *
 * The Renderer draws the map, creatures, and towers using textures.
 * It also manages the TGUI menus for tower selection and pause.
 */
class Renderer {
private:
    sf::RenderWindow& window; ///< Main SFML render window
    tgui::Gui& gui;           ///< GUI manager (TGUI)

    const float tileSize = 48.f; ///< Size of each tile (in pixels)
    bool paused = false; ///< flag for the state of the game (pause/play)

    // Cache of textures to avoid reloading from disk
    std::unordered_map<std::string, sf::Texture> textures;

    // GUI panels
    tgui::Panel::Ptr pausePanel;
    tgui::Panel::Ptr towerMenu;

    /// @brief Load a texture from the "assets/" folder if not already cached.
    sf::Texture& getTexture(const std::string& filename);

    /// @brief Convert pixel coordinates to tile coordinates.
    sf::Vector2i screenToTile(int mouseX, int mouseY) const;

public:
    Renderer(sf::RenderWindow& win, tgui::Gui& g);
    
    // Seed used for deterministic texture generation
    const uint64_t emptyTileSeed = 0x123456789cbcdefULL;

    // Pseudo-random generator from tile coordinates
    uint32_t pseudoRandomFromCoords(int x, int y) const;

    // Deterministically selects an empty-tile texture based on coordinates
    const sf::Texture& chooseEmptyTileTextureAt(int x, int y);

    /// @brief Draws the full game scene.
    void render(const Game& game);

    /// @brief Handles left mouse click to open the tower selection menu.
    void handleMouseClick(int mouseX, int mouseY, Game& game);

    /// @brief Opens a menu to choose which tower to place.
    void openTowerMenu(sf::Vector2i tilePos, Game& game);

    /// @brief Toggles the pause menu on/off.
    void togglePauseMenu(bool isPaused, Game& game);

    /// @brief Shows an error message popup.
    void showError(const std::string& msg);

    /// @brief Draws the HUD of ressources.
    void drawMaterials(const Game& game);
};

#endif // RENDERER_HPP
