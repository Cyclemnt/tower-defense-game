#ifndef LASER_EFFECT_HPP
#define LASER_EFFECT_HPP

#include <array>
#include <SFML/Graphics.hpp>
#include "visualEffect.hpp"
class RenderContext;

class LaserEffect : public VisualEffect {
private:
    sf::Vector2f start, end;
    sf::Color color;
    float lifetime = 0.02f;
    float age = 0.0f;
    
public:
    LaserEffect(std::array<float, 2> s, std::array<float, 2> e);
    void update(float dt) override;
    void render(RenderContext& ctx);
};


#endif // LASER_EFFECT_HPP