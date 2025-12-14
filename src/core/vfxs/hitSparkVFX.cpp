#include <cstdlib>
#include <cmath>
#include "core/vfxs/hitSparkVFX.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

#define PIf 3.141592f

namespace tdg::core {
    
    HitSparkVFX::HitSparkVFX(unsigned int level, float x1, float y1)
        : VFX(level, x1, y1)
    {
        int count = 5 + std::rand() % 5;
        particles.reserve(count);
        for (int i = 0; i < count; ++i) {
            const float angle = (std::rand() % 360) * static_cast<float>(PIf) / 180.0f;
            const float speed = 1.6f + (std::rand() % 100) * 0.002f;
            const float radius = 0.02f + (std::rand() % 30) * 0.001f;
            const float ttl = 0.12f + (std::rand() % 40) * 0.002f;
            particles.emplace_back(std::cos(angle), std::sin(angle), speed, radius, ttl);
        }
        randomizeColor();
    }

    void HitSparkVFX::update(float dt) {
        if (m_timetolive > 0.0f) {
            m_timetolive -= dt;
            for (auto& p : particles) {
                p.timetolive -= dt;
                float t = (p.timetolive - m_lifetime) / m_lifetime; // Progress ratio [0..1]
                p.radius = p.maxRadius * (1.0f - t);
            }

            float t = (m_timetolive - m_lifetime) / m_lifetime; // Progress ratio [0..1]
            // m_color.a = static_cast<unsigned int>(220.0f * (1.0f - t)); trying sinusoid:
            m_color.a = static_cast<unsigned int>(220.0f * (1.0f - t) + 35.0f * std::cos(25.0f * PIf * t));
        }
        else m_alive = false;
    }

    void HitSparkVFX::draw(IVideoRenderer& vidRenderer) const {
        for (auto& p : particles) {
            if (p.timetolive <= 0.0f) continue;

            const float dist = p.speed * (p.lifetime - p.timetolive) * 0.6f;
            float px = m_x1 + p.dirX * dist;
            float py = m_y1 + p.dirY * dist;

            vidRenderer.drawCircle(px, py, p.radius, m_color.r, m_color.g, m_color.b, m_color.a);
        }
    }

    void HitSparkVFX::randomizeColor() {
        unsigned int r = std::rand() % 41; 
        unsigned int g = std::rand() % 41;
        unsigned int b = std::rand() % 41;

        switch (m_level) {
            case 1u: m_color.setColor(235u + r, 214u + g, 35u + b, 0u); break;
            case 2u: m_color.setColor(235u + r, 157u + g, 12u + b, 0u); break;
            case 3u: m_color.setColor(235u + r, 44u + g, 0u + b, 0u);   break;
        }
    }

} // namespace tdg::core
