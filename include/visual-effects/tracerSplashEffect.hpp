#ifndef TRACER_SPLASH_EFFECT_HPP
#define TRACER_SPLASH_EFFECT_HPP

#include "visualEffect.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdint>

struct SimpleParticle {
    float vx, vy;   // direction unit
    float speed;    // tiles/sec
    float radius;   // fraction of tile
    float age;
    float lifetime;
};

class TracerSplashEffect : public VisualEffect {
private:
    sf::Vector2f pos;      // tile coordinates
    sf::Color color;
    std::vector<SimpleParticle> parts;
    float age = 0.0f;
    float lifetime = 0.6f;

public:
    TracerSplashEffect(std::array<float,2> position, sf::Color c);
    void update(float dt) override;
    void render(sf::RenderWindow& w, float tileSize) override;
};

#endif
