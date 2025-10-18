#include <cmath>
#include "../../include/visual-effects/tracerSplashEffect.hpp"
#include "../../include/renderer/renderContext.hpp"

TracerSplashEffect::TracerSplashEffect(std::array<float,2> position, sf::Color c)
    : pos(position[0], position[1]), color(c) {
    int count = 6; // could be random
    parts.reserve(count);
    for (int i = 0; i < count; ++i) {
        float ang = (std::rand() % 360 + i) * M_PIf * 0.005555; // rand * pi / 180
        float spd = 0.6f + (std::rand() % 100) * 0.002f; // 0.6..0.8 tiles/sec
        float rad = 0.02f + (std::rand() % 30) * 0.001f; // 0.02..0.05 tile
        SimpleParticle sp{std::cos(ang), std::sin(ang), spd, rad, 0.0f, 0.12f + (std::rand() % 40) * 0.002f};
        parts.push_back(sp);
    }
}

void TracerSplashEffect::update(float dt) {
    age += dt;
    for (auto &p : parts) p.age += dt;
    if (age >= lifetime) die();
}

void TracerSplashEffect::render(RenderContext& ctx) {
    auto& w = ctx.window;
    auto& tileSize = ctx.tileSize;
    
    float baseX = (pos.x + 0.5f) * tileSize;
    float baseY = (pos.y + 0.5f) * tileSize;
    for (const auto &p : parts) {
        float t = p.age / p.lifetime;
        if (t > 1.f) continue;
        float dist = p.speed * p.age * tileSize * 0.6f; // mm factor for visual scaling
        float px = baseX + p.vx * dist;
        float py = baseY + p.vy * dist;
        float r = p.radius * tileSize * (1.0f - t); // shrink
        sf::CircleShape dot(r);
        dot.setOrigin({r, r});
        dot.setPosition({px, py});
        std::uint8_t a = static_cast<std::uint8_t>(220 * (1.0f - t));
        dot.setFillColor(sf::Color(color.r, color.g, color.b, a));
        w.draw(dot);
    }
}
