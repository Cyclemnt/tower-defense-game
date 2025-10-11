#ifndef TRACER_EFFECT_HPP
#define TRACER_EFFECT_HPP

#include "visualEffect.hpp"
#include "tracerSplashEffect.hpp"
#include <array>

class TracerEffect : public VisualEffect {
private:
    std::array<float, 2> start, end;
    sf::Color color;
    float lifetime = 0.6f;
    float age = 0.0f;
    float jitterX, jitterY;
    TracerSplashEffect tse;

public:
    TracerEffect(std::array<float, 2> start_, std::array<float, 2> end_);
    void update(float dt) override;
    void render(sf::RenderWindow& w, float tileSize) override;
    sf::Color generateRandomColor() const;
};

#endif // TRACER_EFFECT_HPP