#include "core/vfxs/fanucVFX.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

namespace tdg::core {
    
    FanucVFX::FanucVFX(float x1, float y1)
        : VFX(1u, x1, y1)
    {
        m_timetolive = m_lifetime = 120.0f;
    }

    void FanucVFX::update(float dt) {
        ++m_tick;
        if (m_timetolive > 0.0f) {
            computeFade();
            m_timetolive -= std::min(m_timetolive, dt);
        }
        else m_alive = false;
    }

    void FanucVFX::draw(IVideoRenderer& vidRenderer) const {
        unsigned int frame = m_tick / 64 % 4;
        std::string spriteId = "vfx/fanuc_" + std::to_string(frame);
        vidRenderer.drawSprite(spriteId, m_x1, m_y1, 1.0f, utils::Color(255,255,255,m_alpha));
    }

    void FanucVFX::computeFade() {
        float timeElapsed = m_lifetime - m_timetolive;

        float fadeIn = timeElapsed / m_fadeDuration;
        float fadeOut = m_timetolive / m_fadeDuration;

        float alphaFactor = std::min(1.0f, std::min(fadeIn, fadeOut));
        
        if (alphaFactor < 0.0f) alphaFactor = 0.0f;

        m_alpha = static_cast<unsigned int>(255.0f * alphaFactor);
    }

} // namespace tdg::core
