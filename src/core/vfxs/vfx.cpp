#include <algorithm>
#include "core/vfxs/vfx.hpp"

namespace tdg::core {
    
    VFX::VFX(unsigned int level, float x1, float y1)
        : m_level(level), m_x1(x1), m_y1(y1) {}

    void VFX::update(float dt) {
        if (m_timetolive > 0.0f) m_timetolive -= dt;
        else m_alive = false;
    }

    void VFX::Color::setColor(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha) {
        r = std::clamp(red, 0u, 255u);
        g = std::clamp(green, 0u, 255u);
        b = std::clamp(blue, 0u, 255u);
        a = std::clamp(alpha, 0u, 255u);
    }

} // namespace tdg::core
