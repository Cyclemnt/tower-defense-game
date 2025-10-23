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
    const Game& game;
    RenderContext ctx;  ///< Rendering context shared with entities

    /// @brief Texture cache to avoid reloading from disk
    std::unordered_map<std::string, sf::Texture> textures;

public:
    explicit Renderer(sf::RenderWindow& win, Game& game);

    /// @brief Returns the render context.
    RenderContext& getContext() { return ctx; }

    /// @brief Loads and caches textures. Returns a reference.
    const sf::Texture& getTexture(const std::string& name, bool smooth = false);

    /// @brief Computes map scaling and centering relative to window.
    void computeScaling();

    /// @brief Renders the entire game scene (map, entities, etc.).
    void render();

    /// @brief Highlights the tile currently under the mouse.
    void highlightTile();
};

#endif // RENDERER_HPP
