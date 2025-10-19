#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "renderContext.hpp"
class Game;

/**
 * @class Renderer
 * @brief Handles all SFML rendering (map, creatures, towers, effects).
 *
 * The Renderer is responsible for all graphical elements of the game world.
 * It no longer handles any TGUI components (handled by GuiManager).
 */
class Renderer {
private:
    RenderContext ctx;  ///< Rendering context shared with entities

    /// @brief Texture cache to avoid reloading from disk
    std::unordered_map<std::string, sf::Texture> textures;

public:
    explicit Renderer(sf::RenderWindow& win);

    /// @brief Returns the render context.
    RenderContext& getContext() { return ctx; }

    /// @brief Loads and caches textures. Returns a reference.
    const sf::Texture& getTexture(const std::string& name);

    /// @brief Computes map scaling and centering relative to window.
    void computeScaling(const Game& game);

    /// @brief Converts mouse coordinates to tile coordinates.
    sf::Vector2i screenToTile(int mouseX, int mouseY) const;

    /// @brief Renders the entire game scene (map, entities, etc.).
    void render(const Game& game);

    /// @brief Highlights the tile currently under the mouse.
    void highlightTile(const Game& game);
};

#endif // RENDERER_HPP
