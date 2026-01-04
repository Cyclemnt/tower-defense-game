#include <cmath>
#include "core/vfxs/fireflyVFX.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

namespace tdg::core {
    
    FireflyVFX::FireflyVFX(float x1, float y1)
        : VFX(1u, x1, y1)
    {
        m_timetolive = m_lifetime = 90.0f;
    }

    void FireflyVFX::update(float dt) {
        if (m_timetolive > 0.0f) {
            m_timetolive -= std::min(m_timetolive, dt);
            computeFade();
            randomizePosition(dt);
        }
        else m_alive = false;
    }

    void FireflyVFX::draw(IVideoRenderer& vidRenderer) const {
        vidRenderer.drawSprite("vfx/firefly", m_x1, m_y1, 1.0f, utils::Color(255,255,255,m_alpha));
    }

    void FireflyVFX::computeFade() {
        float timeElapsed = m_lifetime - m_timetolive;

        float fadeIn = timeElapsed / m_fadeDuration;
        float fadeOut = m_timetolive / m_fadeDuration;

        float alphaFactor = std::min(1.0f, std::min(fadeIn, fadeOut));
        
        if (alphaFactor < 0.0f) alphaFactor = 0.0f;

        m_alpha = static_cast<unsigned int>(255.0f * alphaFactor);
    }

    void FireflyVFX::randomizePosition(float dt) {
        float t = (m_lifetime - m_timetolive) * 0.6f;
        float r = static_cast<float>(std::rand()) / RAND_MAX - 0.5f;

        m_x1 += std::cos(t + r) * 0.003f;
        m_y1 += std::sin(t * 1.3f - r) * 0.003f;
    }

} // namespace tdg::core
