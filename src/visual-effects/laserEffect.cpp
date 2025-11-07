#include <cmath>
#include <SFML/System/Angle.hpp>
#include "../../include/visual-effects/laserEffect.hpp"
#include "../../include/renderer/renderContext.hpp"

LaserEffect::LaserEffect(sf::Vector2f start_, sf::Vector2f end_)
    : start(start_), end(end_) {}

void LaserEffect::update(float dt) {
    age += dt;
    if (age >= lifetime && appeared) die();
}

void LaserEffect::render(const RenderContext& ctx) {
    const float tileSize = ctx.tileSize;

    const sf::Vector2f startOffset{0.5f, -0.2f};
    const sf::Vector2f endOffset{0.5f, 0.5f};
    const sf::Vector2f startPoint = (start + startOffset) * tileSize + ctx.offset;
    const sf::Vector2f endPoint   = (end + endOffset) * tileSize + ctx.offset;

    const sf::Vector2f diff = endPoint - startPoint;
    const float length = diff.length();
    const sf::Angle angleDeg = diff.angle();

    // Outer glow
    sf::RectangleShape glow({length, tileSize * 0.12f});
    glow.setOrigin({0.0f, (tileSize * 0.12f) * 0.5f});
    glow.setPosition(startPoint);
    glow.setRotation(angleDeg);
    glow.setFillColor(sf::Color(255, 180, 50, 80));

    // Inner beam
    sf::RectangleShape beam({length, tileSize * 0.06f});
    beam.setOrigin({0.0f, (tileSize * 0.06f) * 0.5f});
    beam.setPosition(startPoint);
    beam.setRotation(angleDeg);
    beam.setFillColor(sf::Color(255, 100, 0, 230));

    ctx.window.draw(glow);
    ctx.window.draw(beam);
    appeared = true;
}
