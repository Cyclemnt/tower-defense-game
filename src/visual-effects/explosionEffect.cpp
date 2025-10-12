#include <cstdint>
#include "../../include/visual-effects/explosionEffect.hpp"

ExplosionEffect::ExplosionEffect(std::array<float, 2> position, float radius)
        : pos(position[0], position[1]), maxRadius(radius) {}

void ExplosionEffect::update(float dt) {
    age += dt;
    if (age >= lifetime) die();
}

void ExplosionEffect::render(sf::RenderWindow& w, float tileSize) {
    float t = age / lifetime; // 0..1
    float r = maxRadius * (1.0f - (1.0f - t) * (1.0f - t)); // ease-out
    float px = (pos.x + 0.5f) * tileSize;
    float py = (pos.y + 0.5f) * tileSize;

    // glow (bigger, transparent)
    sf::CircleShape glow(r * tileSize * 1.6f);
    glow.setOrigin({glow.getRadius(), glow.getRadius()});
    glow.setPosition({px, py});
    glow.setFillColor(sf::Color(255, 180, 60, static_cast<std::uint8_t>(180 * (1 - t))));
    w.draw(glow);

    // core (smaller, brighter)
    sf::CircleShape core(r * tileSize * 0.8f);
    core.setOrigin({core.getRadius(), core.getRadius()});
    core.setPosition({px, py});
    core.setFillColor(sf::Color(255, 120, 0, static_cast<std::uint8_t>(220 * (1 - t))));
    w.draw(core);
}
