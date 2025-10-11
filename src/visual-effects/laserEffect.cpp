#include "../../include/visual-effects/laserEffect.hpp"
#include <cmath>
#include <SFML/System/Angle.hpp>

LaserEffect::LaserEffect(std::array<float, 2> s, std::array<float, 2> e)
    : start(s), end(e) {}

void LaserEffect::update(float dt) {
    age += dt;
    if (age >= lifetime)
        die();
}

void LaserEffect::render(sf::RenderWindow& w, float tileSize) {
    sf::Vector2f startPoint = {(start[0] + 0.5f) * tileSize,
                               (start[1] + 0.5f) * tileSize};
    sf::Vector2f endPoint   = {(end[0] + 0.5f) * tileSize,
                               (end[1] + 0.5f) * tileSize};

    sf::Vector2f diff = endPoint - startPoint;
    float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    float angleDeg = std::atan2(diff.y, diff.x) * 180.f / 3.1415926f;

    sf::RectangleShape glow(sf::Vector2f(length, tileSize * 0.12f));
    glow.setOrigin({0.0f, (tileSize * 0.12f) * 0.5f});
    glow.setPosition(startPoint);
    glow.setRotation(sf::degrees(angleDeg));
    glow.setFillColor(sf::Color(255, 180, 50, 80));

    sf::RectangleShape beam(sf::Vector2f(length, tileSize * 0.06f));
    beam.setOrigin({0.0f, (tileSize * 0.06f) * 0.5f});
    beam.setPosition(startPoint);
    beam.setRotation(sf::degrees(angleDeg));
    beam.setFillColor(sf::Color(255, 100, 0, 230));

    w.draw(glow);
    w.draw(beam);
}
