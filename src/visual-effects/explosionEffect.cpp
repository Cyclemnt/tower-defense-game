#include <cstdint>
#include "../../include/visual-effects/explosionEffect.hpp"
#include "../../include/renderer/renderContext.hpp"

ExplosionEffect::ExplosionEffect(sf::Vector2f position_, float maxRadius_)
    : position(position_), maxRadius(maxRadius_) {}

void ExplosionEffect::update(float dt) {
    age += dt;
    if (age >= lifetime) die();
}

void ExplosionEffect::render(const RenderContext& ctx) {
    const float t = age / lifetime; // progress ratio [0..1]
    const float r = maxRadius * (1.0f - (1.0f - t) * (1.0f - t)); // ease-out
    const sf::Vector2f pos = (position + sf::Vector2f(0.5f, 0.5f)) * ctx.tileSize + ctx.offset;

    // Outer glow
    sf::CircleShape glow(r * ctx.tileSize * 1.6f);
    glow.setOrigin({glow.getRadius(), glow.getRadius()});
    glow.setPosition(pos);
    std::uint8_t a = static_cast<std::uint8_t>(180.0f * (1.0f - t));
    glow.setFillColor(sf::Color(255, 180, 60, a));
    ctx.window.draw(glow);

    // Bright core
    sf::CircleShape core(r * ctx.tileSize * 0.8f);
    core.setOrigin({core.getRadius(), core.getRadius()});
    core.setPosition(pos);
    a = static_cast<std::uint8_t>(220 * (1.0f - t));
    core.setFillColor(sf::Color(255, 120, 0, a));
    ctx.window.draw(core);
}
