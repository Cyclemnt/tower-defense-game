#include "core/vfxs/explosionVFX.hpp"

namespace tdg::core {
    
    ExplosionVFX::ExplosionVFX(unsigned int level, float x1, float y1)
        : VFX(level, x1, y1)
    {
        m_timetolive = m_lifetime;
        setColor(255u, 120u, 0u, 220u);
    }

    void ExplosionVFX::update(float dt) {
        float t = (m_timetolive - m_lifetime) / m_lifetime; // Progress ratio [0..1]
        m_radius = m_maxRadius * (1.0f - (1.0f - t) * (1.0f - t)); // Ease-out
        m_alpha = static_cast<unsigned int>(220u * (1.0f - t));
    }

} // namespace tdg::core
