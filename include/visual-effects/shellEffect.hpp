#ifndef SHELL_EFFECT_HPP
#define SHELL_EFFECT_HPP

#include "visualEffect.hpp"
#include <cmath>

class ShellEffect : public VisualEffect {
private:
    sf::Vector2f pos;
    sf::Vector2f target;
    float speed;
    float lifetime = 5.0f;
    float radius = 0.1f;

public:
    ShellEffect(sf::Vector2f start, sf::Vector2f end, float spd);
    void update(float dt) override;
    void render(sf::RenderWindow& w, float tileSize);
    sf::Vector2f getPos() const;
};

#endif
