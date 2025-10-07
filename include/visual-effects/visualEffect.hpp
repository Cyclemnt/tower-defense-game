#ifndef VISUAL_EFFECT_HPP
#define VISUAL_EFFECT_HPP

#include <SFML/Graphics.hpp>

class VisualEffect {
public:
    virtual ~VisualEffect() = default;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window, float tileSize) const = 0;
    virtual bool isAlive() const = 0;
};

#endif
