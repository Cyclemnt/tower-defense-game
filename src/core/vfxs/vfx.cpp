#include <algorithm>
#include "core/vfxs/vfx.hpp"

namespace tdg::core {
    
    VFX::VFX(unsigned int level, float x1, float y1, std::optional<float> x2, std::optional<float> y2)
        : m_level(level), m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2) {}

    void VFX::update(float dt) {
        if (m_timetolive > 0.0f) m_timetolive -= dt;
        else m_alive = false;
    }

    void VFX::setColor(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha) {
        m_red = std::clamp(red, 0u, 255u);
        m_green = std::clamp(green, 0u, 255u);
        m_blue = std::clamp(blue, 0u, 255u);
        m_alpha = std::clamp(alpha, 0u, 255u);
    }

} // namespace tdg::core
