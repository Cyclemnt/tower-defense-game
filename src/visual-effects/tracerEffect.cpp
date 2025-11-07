#include <cmath>
#include <cstdlib>
#include "../../include/visual-effects/tracerEffect.hpp"
#include "../../include/renderer/renderContext.hpp"
#include <iostream>
TracerEffect::TracerEffect(sf::Vector2f start_, sf::Vector2f end_)
    : start(start_), end(end_), color(generateRandomColor()), splash(end_, color)
{
    jitterX = ((std::rand() % 200) * 0.001f - 0.1f);
    jitterY = ((std::rand() % 200) * 0.001f - 0.1f);
}

void TracerEffect::update(float dt) {
    splash.update(dt);
    age += dt;
    if (age >= lifetime) die();
}

void TracerEffect::render(const RenderContext& ctx) {
    splash.render(ctx);
    if (age >= 0.05f && appeared) return;

    const sf::Vector2f startOffset{0.5f, 0.3f};
    const sf::Vector2f endOffset{0.5f, 0.5f};
    const sf::Vector2f startPoint = (start + startOffset) * ctx.tileSize + ctx.offset;
    const sf::Vector2f endPoint   = (end + endOffset) * ctx.tileSize + ctx.offset;

    const sf::Vector2f diff = endPoint - startPoint;
    const float length = diff.length();

    sf::RectangleShape beam({length, 2.5f});
    beam.setOrigin({0.0f, 1.25f});
    beam.setPosition(startPoint);
    beam.setRotation(diff.angle());
    beam.setFillColor(color);

    ctx.window.draw(beam);
    appeared = true;
}

sf::Color TracerEffect::generateRandomColor() const {
    int r = 200 + std::rand() % 56;
    int g = 200 + std::rand() % 56;
    int b = 50 + std::rand() % 50;
    return sf::Color(r, g, b);
}
