#include "../../include/visual-effects/tracerEffect.hpp"
#include <cstdlib>  // Pour rand()
#include <ctime>    // Pour time()

TracerEffect::TracerEffect(std::array<float, 2> s, std::array<float, 2> e, sf::Color c, float duration)
    : start(s), end(e), lifetime(duration), color(c) {}

void TracerEffect::update(float dt) { lifetime -= dt; }

void TracerEffect::render(sf::RenderWindow& w, float tileSize) const {
    std::array<sf::Vertex, 2> line;

    line[0].position = {(start[0] + 0.5f + (std::rand() % 201) / 1000.0 - 0.1) * tileSize, (start[1] + 0.5f + (std::rand() % 201) / 1000.0 - 0.1) * tileSize};
    line[1].position = {(end[0] + 0.5f + (std::rand() % 201) / 1000.0 - 0.1) * tileSize, (end[1] + 0.5f + (std::rand() % 201) / 1000.0 - 0.1) * tileSize};
    line[0].color = color;
    line[1].color = color;

    w.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
    // TODO: ADD SPLASH ON CREATURE (END)
}

bool TracerEffect::isAlive() const { return lifetime > 0.f; }