#ifndef RENDER_CONTEXT_HPP
#define RENDER_CONTEXT_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Renderer;

/**
 * @class RenderContext
 * @brief Shared rendering environment for all drawable entities.
 *
 * This structure encapsulates rendering data such as:
 * - the window reference
 * - tile size (world-to-pixel scale)
 * - camera offset
 * - global tick count
 * - link to the Renderer for texture retrieval
 */
class RenderContext {
public:
    sf::RenderWindow& window; ///< Reference to the active SFML window.
    Renderer& renderer;       ///< Reference to the renderer managing textures.

    float tileSize = 64.0f;   ///< Size of one tile in pixels.
    sf::Vector2f offset{0.0f, 0.0f}; ///< Offset (camera position) in pixels.
    unsigned long tick = 0;   ///< Global simulation tick.
    sf::Vector2u lastWinSize; ///< Last known window size (for resize detection).

public:
    /// @brief Constructs a new rendering context.
    /// @param w Reference to the SFML window.
    /// @param r Reference to the renderer.
    /// @param ts Initial tile size (default: 64 pixels).
    /// @param t Initial tick count (default: 0).
    RenderContext(sf::RenderWindow& w, Renderer& r) noexcept;

    /// @brief Converts a pixel position (mouse or screen) to tile coordinates.
    /// @param mouseX X coordinate in pixels.
    /// @param mouseY Y coordinate in pixels.
    /// @return Tile coordinates as integer grid indices.
    [[nodiscard]] sf::Vector2i screenToTile(const sf::Vector2i& mousePos) const noexcept;

    /// @brief Checks if a tile/world position is visible on screen.
    /// @param position Tile position in world coordinates.
    /// @return True if the position is visible within the current view.
    [[nodiscard]] bool isOnScreen(const sf::Vector2f& position) const noexcept;
};

#endif // RENDER_CONTEXT_HPP
