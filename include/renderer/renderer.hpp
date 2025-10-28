#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "renderContext.hpp"

class Game;

/**
 * @class Renderer
 * @brief Manages all rendering operations for the game world.
 *
 * The Renderer handles:
 * - texture caching and retrieval
 * - tile scaling and map centering
 * - rendering of map, towers, creatures, and effects
 * - visual feedback (e.g., build zone highlight)
 *
 * It intentionally excludes UI logic (handled separately by GuiManager).
 */
class Renderer {
private:
    const Game& game;   ///< Reference to the main Game instance.
    RenderContext ctx;  ///< Shared rendering context for entities.

    /// @brief Texture cache to avoid redundant disk loads.
    std::unordered_map<std::string, sf::Texture> textures;

public:
    /// @brief Constructs a new Renderer.
    /// @param window The render window reference.
    /// @param game Reference to the game being rendered.
    explicit Renderer(sf::RenderWindow& window_, Game& game_);

    /// @brief Returns a reference to the rendering context.
    [[nodiscard]] RenderContext& getContext() noexcept { return ctx; }

    /// @brief Loads and caches a texture.
    /// @param name File name (relative to the textures directory).
    /// @param smooth Whether to apply smoothing.
    /// @return A const reference to the loaded texture.
    [[nodiscard]] const sf::Texture& getTexture(const std::string& name, bool smooth = false);

    /// @brief Recomputes the tile scaling and centering based on window size.
    void computeScaling();

    /// @brief Renders the entire scene (map, entities, effects, highlights).
    void render();

private:
    /// @brief Highlights the tile currently under the mouse cursor.
    void highlightTile();
};

#endif // RENDERER_HPP
