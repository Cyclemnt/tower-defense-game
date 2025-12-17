#include "core/vfxs/laserBeamVFX.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

namespace tdg::core {
    
    LaserBeamVFX::LaserBeamVFX(unsigned int level, float x1, float y1, float x2, float y2)
        : VFX(level, x1, y1), m_x2(x2), m_y2(y2)
    {
        m_timetolive = m_lifetime = 0.17f;
        switch (m_level) {
            case 1u: m_color.setColor(255u,234u,55u,230u); m_glow.setColor(255u,255u,130u,80u); break;
            case 2u: m_color.setColor(255u,177u,32u,230u); m_glow.setColor(255u,150u,80u,80u);  break;
            case 3u: m_color.setColor(255u,64u,20u,230u);  m_glow.setColor(255u,120u,80u,80u);  break;
            
            default: break;
        }
    }

    void LaserBeamVFX::update(float dt) {
        if (m_timetolive > 0.0f) {
            m_timetolive -= std::min(m_timetolive, dt);
            float t = (m_lifetime - m_timetolive) / m_lifetime; // Progress ratio [0..1]
            t = t * t;
            m_color.a = static_cast<unsigned int>(230.0f * (1.0f - t));
            m_glow.a = static_cast<unsigned int>(80.0f * (1.0f - t));
        }
        else m_alive = false;
    }

    void LaserBeamVFX::draw(IVideoRenderer& vidRenderer) const {
        // Outer glow
        vidRenderer.drawLine(m_x1 + 0.5f, m_y1 - 0.3f, m_x2 + 0.5f, m_y2 + 0.5f, 0.12f, m_glow);
        // Inner beam
        vidRenderer.drawLine(m_x1 + 0.5f, m_y1 - 0.3f, m_x2 + 0.5f, m_y2 + 0.5f, 0.06f, m_color);
    }

} // namespace tdg::core
