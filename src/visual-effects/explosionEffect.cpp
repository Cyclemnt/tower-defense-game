#include "../../include/visual-effects/explosionEffect.hpp"

ExplosionEffect::ExplosionEffect(sf::Vector2f pos, float r, float d)
    : center(pos), radius(r), lifetime(d) {}

void ExplosionEffect::update(float dt) { lifetime -= dt; }

void ExplosionEffect::render(sf::RenderWindow& w, float tileSize) const {
    sf::CircleShape circle(tileSize * radius);
    circle.setPosition({center.x * tileSize - radius * tileSize,
                        center.y * tileSize - radius * tileSize});
    circle.setFillColor(sf::Color(255, 120, 0, 180));
    w.draw(circle);
}

bool ExplosionEffect::isAlive() const { return lifetime > 0.f; }