#include <algorithm>
#include "core/vfxs/vfx.hpp"

namespace tdg::core {
    
    VFX::VFX(unsigned int level, float x1, float y1)
        : m_level(level), m_x1(x1), m_y1(y1) {}

    void VFX::update(float dt) {
        if (m_timetolive > 0.0f) m_timetolive -= std::min(m_timetolive, dt);
        else m_alive = false;
    }

} // namespace tdg::core
