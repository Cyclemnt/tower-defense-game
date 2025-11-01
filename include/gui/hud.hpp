#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include "../game.hpp"
#include "../renderer/renderContext.hpp"

/**
 * @class HUD
 * @brief Draws the top HUD: materials, cores, FPS, current wave and next-wave timer.
 *
 * The HUD reads game state (materials, cores, wave info) and draws a small overlay
 * using SFML primitives. It is lightweight and intended to be called every frame
 * after the world is rendered.
 */
class HUD {
private:
    sf::Font font;        ///< Font used for textual HUD elements
    sf::Clock fpsClock;   ///< Small clock used to throttle FPS calculation
    float lastFPS = 0.0f; ///< Last computed FPS value (integer-ish for display)
    float lastMemoryMB = 0.0f;

    const RenderContext& ctx; ///< Render context (tileSize, offset, window)
    const Game& game;         ///< Read-only reference to the game state

    // --- Drawing helpers ---
    void drawResourcesPanel() const;
    void drawCores(sf::Vector2f position, float width, float scale) const;
    void drawWavePanel(float scale) const;
    void drawFPSPanel(float scale) const;

    void drawGameOver() const;
    void drawVictory() const;

public:
    /// @brief Construct the HUD.
    /// @param ctx_ RenderContext used for sizes and window reference.
    /// @param game_ Reference to the main Game.
    HUD(const RenderContext& ctx_, const Game& game_);

    /// @brief Draw HUD. Must be called every frame after renderer.
    /// @param deltaTime Elapsed time since last frame (seconds).
    void draw(float deltaTime);    
};

#endif // HUD_HPP
