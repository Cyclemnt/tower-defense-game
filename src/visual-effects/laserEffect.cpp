#include "../../include/visual-effects/laserEffect.hpp"

LaserEffect::LaserEffect(sf::Vector2f s, sf::Vector2f e)
    : start(s), end(e) {}

void LaserEffect::update(float dt) { lifetime -= dt; }

void LaserEffect::render(sf::RenderWindow& w, float tileSize) const {
    std::array<sf::Vertex, 2> beam;

    beam[0].position = start * tileSize;
    beam[1].position = end * tileSize;
    beam[0].color = sf::Color::Red;
    beam[1].color = sf::Color::Red;

    w.draw(beam.data(), beam.size(), sf::PrimitiveType::Lines);
}

bool LaserEffect::isAlive() const { return lifetime > 0.f; }