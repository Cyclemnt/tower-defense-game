#ifndef SHELL_EFFECT_HPP
#define SHELL_EFFECT_HPP

#include <array>
#include <SFML/Graphics.hpp>
#include "visualEffect.hpp"
class RenderContext;

class ShellEffect : public VisualEffect {
private:
    sf::Vector2f pos;
    sf::Vector2f target;
    float speed;
    float lifetime = 5.0f;
    float radius = 0.1f;

public:
    ShellEffect(std::array<float, 2> start, std::array<float, 2> end, float spd);
    void update(float dt) override;
    void render(RenderContext& ctx);
    sf::Vector2f getPos() const;
};

#endif
