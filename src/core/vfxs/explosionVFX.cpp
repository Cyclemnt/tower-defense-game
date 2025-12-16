#include "core/vfxs/explosionVFX.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

namespace tdg::core {
    
    ExplosionVFX::ExplosionVFX(unsigned int level, float x1, float y1)
        : VFX(level, x1, y1)
    {
        m_timetolive = m_lifetime = 0.3f;
        switch (m_level) {
            case 1u: m_color.setColor(255u,234u,55u,230u); m_glow.setColor(255u,255u,130u,80u); break;
            case 2u: m_color.setColor(255u,177u,32u,230u); m_glow.setColor(255u,150u,80u,80u);  break;
            case 3u: m_color.setColor(255u,64u,20u,230u);  m_glow.setColor(255u,120u,80u,80u);  break;
            
            default: break;
        }
    }

    void ExplosionVFX::update(float dt) {
        if (m_timetolive > 0.0f) {
            m_timetolive -= std::min(m_timetolive, dt);

            float t = (m_lifetime - m_timetolive) / m_lifetime; // Progress ratio [0..1]
            m_radius = m_maxRadius * (1.0f - (1.0f - t) * (1.0f - t)); // Ease-out
            m_color.a = static_cast<unsigned int>(220.0f * (1.0f - t));
            m_glow.a = static_cast<unsigned int>(180.0f * (1.0f - t));
        }
        else m_alive = false;
    }

    void ExplosionVFX::draw(IVideoRenderer& vidRenderer) const {
        // Outer glow
        vidRenderer.drawCircle(m_x1 + 0.5f, m_y1 + 0.5f, m_radius * 1.6f, m_glow);
        // Inner core
        vidRenderer.drawCircle(m_x1 + 0.5f, m_y1 + 0.5f, m_radius * 0.8f, m_color);
    }

} // namespace tdg::core
