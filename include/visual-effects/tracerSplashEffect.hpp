#ifndef TRACER_SPLASH_EFFECT_HPP
#define TRACER_SPLASH_EFFECT_HPP

#include "visualEffect.hpp"
#include <array>
#include <SFML/Graphics.hpp>

class SplashEffect : public VisualEffect {
private:
    std::array<float, 2> position;
    float lifetime;
    sf::Color color;

public:
    SplashEffect(std::array<float, 2> pos, sf::Color c, float duration = 0.1f);
    void update(float dt) override;
    void render(sf::RenderWindow& w, float tileSize) const override;
    bool isAlive() const override;
};

#endif // TRACER_SPLASH_EFFECT_HPP
