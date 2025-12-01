#define _USE_MATH_DEFINES
#include <cmath>
#include "../../include/visual-effects/tracerSplashEffect.hpp"
#include "../../include/renderer/renderContext.hpp"


TracerSplashEffect::TracerSplashEffect(sf::Vector2f position_, sf::Color color_)
    : position(position_), color(color_)
{
    constexpr int count = 6;
    particles.reserve(count);
    for (int i = 0; i < count; ++i) {
        const float ang = (std::rand() % 360) * static_cast<float>(M_PI) / 180.0f;
        const float spd = 1.6f + (std::rand() % 100) * 0.002f;
        const float rad = 0.02f + (std::rand() % 30) * 0.001f;
        particles.push_back({{std::cos(ang), std::sin(ang)}, spd, rad, 0.0f, 0.12f + (std::rand() % 40) * 0.002f});
    }
}

void TracerSplashEffect::update(float dt) {
    age += dt;
    for (auto& p : particles) p.age += dt;
    if (age >= lifetime) die();
}

void TracerSplashEffect::render(const RenderContext& ctx) {
    for (const auto& p : particles) {
        const float t = p.age / p.lifetime;
        if (t > 1.0f) continue;

        const float dist = p.speed * p.age * ctx.tileSize * 0.6f;
        const float r = p.radius * ctx.tileSize * (1.0f - t);
        const sf::Vector2f pos = (position + sf::Vector2f(0.5f, 0.5f) + p.v * dist / ctx.tileSize) * ctx.tileSize + ctx.offset;

        sf::CircleShape dot(r);
        dot.setOrigin({r, r});
        dot.setPosition(pos);
        std::uint8_t a = static_cast<std::uint8_t>(220 * (1.0f - t));
        dot.setFillColor({color.r, color.g, color.b, a});
        ctx.window.draw(dot);
    }
}
