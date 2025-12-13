#include <cstdlib>
#include <cmath>
#include "core/vfxs/hitSparkVFX.hpp"

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
            particles.push_back({std::cos(angle), std::sin(angle), speed, radius, 0.12f + (std::rand() % 40) * 0.002f});
        }
        randomizeColor();
    }

    void HitSparkVFX::randomizeColor() {
        unsigned int r = std::rand() % 41; 
        unsigned int g = std::rand() % 41;
        unsigned int b = std::rand() % 41;

        switch (m_level) {
            case 1u: setColor(235u + r, 214u + g, 35u + b, 0u); break;
            case 2u: setColor(235u + r, 157u + g, 12u + b, 0u); break;
            case 3u: setColor(235u + r, 44u + g, 0u + b, 0u); break;
        }
    }

    void HitSparkVFX::update(float dt) {
        if (m_timetolive > 0.0f) {
            m_timetolive -= dt;
            for (auto& p : particles) p.timetolive -= dt;
        }
        else m_alive = false;
    }

} // namespace tdg::core
