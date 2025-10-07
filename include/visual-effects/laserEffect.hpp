#ifndef LASER_EFFECT_HPP
#define LASER_EFFECT_HPP

#include "visualEffect.hpp"

class LaserEffect : public VisualEffect {
private:
    sf::Vector2f start, end;
    float lifetime = 0.05f;

public:
    LaserEffect(sf::Vector2f s, sf::Vector2f e);
    void update(float dt) override;
    void render(sf::RenderWindow& w, float tileSize) const;
    bool isAlive() const override;
};


#endif // LASER_EFFECT_HPP