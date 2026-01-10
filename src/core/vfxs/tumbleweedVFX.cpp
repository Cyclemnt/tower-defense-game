#include <cmath>
#include "core/vfxs/tumbleweedVFX.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

namespace tdg::core {
    
    TumbleweedVFX::TumbleweedVFX(float x1, float y1)
        : VFX(1u, x1, y1)
    {
        // World limits
        const float minX = -5.0f; const float maxX = 33.0f;

        float r0 = static_cast<float>(std::rand()) / RAND_MAX;
        m_x1 = minX + r0 * (maxX - minX);

        // Final x computing
        float r1 = static_cast<float>(std::rand()) / RAND_MAX;
        float xFinal = m_x1 + r1 * (maxX - m_x1);

        // Corresponding lifetime
        m_lifetime = m_timetolive = (xFinal - m_x1) / m_speed;
    }

    void TumbleweedVFX::update(float dt) {
        ++m_tick;
        if (m_timetolive > 0.0f) {
            m_timetolive -= std::min(m_timetolive, dt);
            computeFade();
            randomizePosition(dt);
        }
        else m_alive = false;
    }

    void TumbleweedVFX::draw(IVideoRenderer& vidRenderer) const {
        int frame = m_tick / 18 % 4;
        std::string id = "vfx/tumbleweed_" + std::to_string(frame);
        vidRenderer.drawSprite(id, m_x1, m_y1, 1.0f, utils::Color(255,255,255,m_alpha));
    }

    void TumbleweedVFX::computeFade() {
        float timeElapsed = m_lifetime - m_timetolive;

        float fadeIn = timeElapsed / m_fadeDuration;
        float fadeOut = m_timetolive / m_fadeDuration;

        float alphaFactor = std::min(1.0f, std::min(fadeIn, fadeOut));
        
        if (alphaFactor < 0.0f) alphaFactor = 0.0f;

        m_alpha = static_cast<unsigned int>(255.0f * alphaFactor);
    }

    void TumbleweedVFX::randomizePosition(float dt) {
        if (dt == 0.0f) return;

        float t = (m_lifetime - m_timetolive) * 0.6f;
        float r = static_cast<float>(std::rand()) / RAND_MAX - 0.5f;

        m_x1 += std::cos(t + r) * 0.02f;
        m_x1 += m_speed * dt;
        m_y1 += std::sin(t * 1.7f - r) * 0.01f;
    }

} // namespace tdg::core
