#include <cmath>
#include "../../include/visual-effects/shellEffect.hpp"
#include "../../include/renderer/renderContext.hpp"

ShellEffect::ShellEffect(sf::Vector2f start_, sf::Vector2f end_, float speed_)
    : position(start_), target(end_), speed(speed_) {}

void ShellEffect::update(float dt) {
    lifetime -= dt;
    if (lifetime <= 0.f) die();

    sf::Vector2f dir = target - position;
    const float dist = dir.length();

    if (dist <= speed * dt) die(); // reached target
    else {
        dir /= dist;
        position += dir * (speed * dt);
    }
}

void ShellEffect::render(const RenderContext& ctx) {
    sf::CircleShape shape(radius * ctx.tileSize);
    shape.setOrigin({radius * ctx.tileSize, radius * ctx.tileSize});
    shape.setFillColor(sf::Color(180, 180, 180));
    sf::Vector2f pos = (position + sf::Vector2f(0.5f, 0.5f)) * ctx.tileSize + ctx.offset;
    shape.setPosition(pos);

    ctx.window.draw(shape);
}
