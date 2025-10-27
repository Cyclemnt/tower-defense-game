#ifndef EXPLOSION_EFFECT_HPP
#define EXPLOSION_EFFECT_HPP

#include <array>
#include <SFML/Graphics.hpp>
#include "visualEffect.hpp"
class RenderContext;

class ExplosionEffect : public VisualEffect {
private:
    sf::Vector2f pos;
    float age = 0.0f;
    float lifetime = 0.3f;
    float maxRadius;

public:
    ExplosionEffect(sf::Vector2f position, float radius = 0.6f);
    void update(float dt) override;
    void render(RenderContext& ctx) override;
};

#endif // EXPLOSION_EFFECT_HPP
