#ifndef TRACER_EFFECT_HPP
#define TRACER_EFFECT_HPP

#include <array>
#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Dense>
#include "visualEffect.hpp"
#include "tracerSplashEffect.hpp"
class RenderContext;

class TracerEffect : public VisualEffect {
private:
    sf::Vector2f start, end;
    sf::Color color;
    float lifetime = 0.6f;
    float age = 0.0f;
    float jitterX, jitterY;
    TracerSplashEffect tse;

public:
    TracerEffect(sf::Vector2f start_, sf::Vector2f end_);
    void update(float dt) override;
    void render(RenderContext& ctx) override;
    sf::Color generateRandomColor() const;
};

#endif // TRACER_EFFECT_HPP