#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include "../game.hpp"
#include "../renderer/renderContext.hpp"

/**
 * HUD: draws player resources, cores and FPS using SFML primitives.
 * It's drawn after the world by calling hud.render(renderer.getContext(), game).
 */
class HUD {
private:
    sf::Font font;
    sf::Clock fpsClock;
    float lastFPS = 0.0f;

    const RenderContext& ctx;
    const Game& game;

    void drawResources();
    void drawCores(float x, float y, float width);
    void drawFPS(float x, float y);

public:
    HUD(RenderContext& ctx_, Game& game_);

    /// Draw the HUD. ctx.window is used for drawing.
    void draw(float deltaTime);
};

#endif // HUD_HPP
