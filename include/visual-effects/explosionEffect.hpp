#ifndef EXPLOSION_EFFECT_HPP
#define EXPLOSION_EFFECT_HPP

#include "visualEffect.hpp"

class ExplosionEffect : public VisualEffect {
private:
    sf::Vector2f center;
    float radius;
    float lifetime;
    
public:
    ExplosionEffect(sf::Vector2f pos, float r = 0.3f, float d = 0.2f);

    void update(float dt) override;
    void render(sf::RenderWindow& w, float tileSize) const override;
    bool isAlive() const override;
};


#endif // EXPLOSION_EFFECT_HPP