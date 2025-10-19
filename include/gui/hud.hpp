#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "renderer/renderContext.hpp"

/**
 * HUD: draws player resources, cores and FPS using SFML primitives.
 * It's drawn after the world by calling hud.render(renderer.getContext(), game).
 */
class HUD {
private:
    sf::Font font;
    sf::Clock fpsClock;
    float lastFPS = 0.0f;

    void drawResources(RenderContext& ctx, const Game& game);
    void drawCores(RenderContext& ctx, const Game& game, float x, float y, float width);
    void drawFPS(RenderContext& ctx, float x, float y);

public:
    HUD();

    /// Draw the HUD. ctx.window is used for drawing.
    void render(RenderContext& ctx, const Game& game, float deltaTime);
};

#endif // HUD_HPP
