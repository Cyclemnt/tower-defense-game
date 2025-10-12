#include <cmath>
#include "../../include/visual-effects/shellEffect.hpp"

ShellEffect::ShellEffect(std::array<float, 2> start, std::array<float, 2> end, float spd)
        : pos(start[0], start[1]), target(end[0], end[1]), speed(spd) {}

void ShellEffect::update(float dt) {
    lifetime -= dt;
    if (lifetime <= 0.f) die();

    sf::Vector2f dir = target - pos;
    float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (dist <= speed * dt) die(); // impact
    else {
        dir /= dist;
        pos += dir * (speed * dt);
    }
}

void ShellEffect::render(sf::RenderWindow& w, float tileSize) {
    sf::CircleShape shape(radius * tileSize);
    shape.setOrigin({radius * tileSize, radius * tileSize});
    shape.setFillColor(sf::Color(180, 180, 180));
    shape.setPosition({(pos.x + 0.5f) * tileSize, (pos.y + 0.5f) * tileSize});
    w.draw(shape);
}

sf::Vector2f ShellEffect::getPos() const { return pos; }