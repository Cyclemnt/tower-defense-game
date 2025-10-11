#ifndef LASER_EFFECT_HPP
#define LASER_EFFECT_HPP

#include "visualEffect.hpp"

class LaserEffect : public VisualEffect {
private:
    std::array<float, 2> start, end;
    sf::Color color;
    float lifetime = 0.02f;
    float age = 0.0f;
    
public:
    LaserEffect(std::array<float, 2> s, std::array<float, 2> e);
    void update(float dt) override;
    void render(sf::RenderWindow& w, float tileSize);
};


#endif // LASER_EFFECT_HPP