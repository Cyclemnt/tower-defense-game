#ifndef TRACER_EFFECT_HPP
#define TRACER_EFFECT_HPP

#include "visualEffect.hpp"
#include <array>

class TracerEffect : public VisualEffect {
private:
    std::array<float, 2> start, end;
    float lifetime;
    sf::Color color;

public:
    TracerEffect(std::array<float, 2> s, std::array<float, 2> e, sf::Color c, float duration = 0.01f);
    void update(float dt) override;
    void render(sf::RenderWindow& w, float tileSize) const override;
    bool isAlive() const override;
};

#endif // TRACER_EFFECT_HPP