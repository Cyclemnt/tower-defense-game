#include <cstdlib>
#include "core/vfxs/gatlingTracerVFX.hpp"

namespace tdg::core {
    
    GatlingTracerVFX::GatlingTracerVFX(unsigned int level, float x1, float y1, float x2, float y2)
        : VFX(level, x1, y1, x2, y2)
    {
        randomizeColor();
        randomizeJitter();
    }

    void GatlingTracerVFX::randomizeColor() {
        m_red   = 200 + std::rand() % 56;
        m_green = 200 + std::rand() % 56;
        m_blue  = 50  + std::rand() % 50;
    }

    void GatlingTracerVFX::randomizeJitter() {
        m_jitterX = ((std::rand() % 200) * 0.001f - 0.1f);
        m_jitterY = ((std::rand() % 200) * 0.001f - 0.1f);
    }

} // namespace tdg::core
