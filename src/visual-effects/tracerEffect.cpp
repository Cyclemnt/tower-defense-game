#include <SFML/System/Angle.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "../../include/visual-effects/tracerEffect.hpp"
#include "../../include/renderer/renderContext.hpp"

TracerEffect::TracerEffect(std::array<float, 2> start_, std::array<float, 2> end_)
    : start(start_[0], start_[1]), end(end_[0], end_[1]), color(generateRandomColor()), tse(end_, color) {
        jitterX = ((std::rand() % 200) * 0.001f - 0.1f);
        jitterY = ((std::rand() % 200) * 0.001f - 0.1f);
}

void TracerEffect::update(float dt) {
    tse.update(dt);
    age += dt;
    if (age >= lifetime) die();
}

void TracerEffect::render(RenderContext& ctx) {
    auto& w = ctx.window;
    auto& tileSize = ctx.tileSize;
    
    tse.render(ctx);
    if (age >= 0.05f) return;
    
    sf::Vector2f startOffset = {0.5f, 0.3f};
    sf::Vector2f endOffset = {0.5f, 0.5f};
    sf::Vector2f startPoint = (start + startOffset) * tileSize + ctx.offset;
    sf::Vector2f endPoint   = (end + endOffset) * tileSize + ctx.offset;

    sf::Vector2f diff = endPoint - startPoint;
    float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    float angleDeg = std::atan2(diff.y, diff.x) * 180.f * M_1_PIf; // atan * 180 / pi

    sf::RectangleShape line(sf::Vector2f(length, 2.5f));
    line.setOrigin({0.0f, 1.25f});
    line.setPosition(startPoint);

    line.setRotation(sf::degrees(angleDeg));

    line.setFillColor(color);
    w.draw(line);
}

sf::Color TracerEffect::generateRandomColor() const {
    int r = 200 + std::rand() % 56;
    int g = 200 + std::rand() % 56;
    int b = 50 + std::rand() % 50;
    return sf::Color(r, g, b);
}
