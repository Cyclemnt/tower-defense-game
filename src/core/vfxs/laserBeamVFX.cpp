#include "core/vfxs/laserBeamVFX.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

namespace tdg::core {
    
    LaserBeamVFX::LaserBeamVFX(unsigned int level, float x1, float y1, float x2, float y2)
        : VFX(level, x1, y1), m_x2(x2), m_y2(y2)
    {
        switch (level) {
            case 1u: m_color.setColor(255u, 234u, 55u, 230u); m_glow.setColor(255u,255u,130u,80u); break;
            case 2u: m_color.setColor(255u, 177u, 32u, 230u); m_glow.setColor(255u,150u,80u,80u);  break;
            case 3u: m_color.setColor(255u, 64u, 20u, 230u);  m_glow.setColor(255u,120u,80u,80u);  break;
            
            default: break;
        }
    }

    void LaserBeamVFX::draw(IVideoRenderer& vidRenderer) const {
        // Outer glow
        vidRenderer.drawRectangle(m_x1, m_y1, m_x2, m_y2, 0.12f, m_glow.r, m_glow.g, m_glow.b, m_glow.a);
        // Inner beam
        vidRenderer.drawRectangle(m_x1, m_y1, m_x2, m_y2, 0.06f, m_color.r, m_color.g, m_color.b, m_color.a);
    }

} // namespace tdg::core
