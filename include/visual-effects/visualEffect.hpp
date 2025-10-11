#ifndef VISUAL_EFFECT_HPP
#define VISUAL_EFFECT_HPP

#include <SFML/Graphics.hpp>

class VisualEffect {
private:
    bool alive = true;

public:
    virtual ~VisualEffect() = default;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window, float tileSize) = 0;
    bool isAlive() const;
    void die();
};

#endif // VISUAL_EFFECT_HPP
