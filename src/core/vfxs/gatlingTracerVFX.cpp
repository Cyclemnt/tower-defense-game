#include <cstdlib>
#include "core/vfxs/gatlingTracerVFX.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

namespace tdg::core {
    
    GatlingTracerVFX::GatlingTracerVFX(unsigned int level, float x1, float y1, float x2, float y2)
        : VFX(level, x1, y1), m_x2(x2), m_y2(y2)
    {
        randomizeColor();
        randomizeJitter();
    }

    void GatlingTracerVFX::draw(IVideoRenderer& vidRenderer) const {
        vidRenderer.drawRectangle(m_x1, m_y1, m_x2 + m_jitterX, m_y2 + m_jitterY, 0.03125f, m_color.r, m_color.g, m_color.b, m_color.a);
    }

    void GatlingTracerVFX::randomizeColor() {
        unsigned int r = std::rand() % 41; 
        unsigned int g = std::rand() % 41;
        unsigned int b = std::rand() % 41;

        switch (m_level) {
            case 1u: m_color.setColor(235u + r, 214u + g, 35u + b, 0u); break;
            case 2u: m_color.setColor(235u + r, 157u + g, 12u + b, 0u); break;
            case 3u: m_color.setColor(235u + r, 44u + g, 0u + b, 0u); break;
        }
    }

    void GatlingTracerVFX::randomizeJitter() {
        m_jitterX = ((std::rand() % 200) * 0.001f - 0.1f);
        m_jitterY = ((std::rand() % 200) * 0.001f - 0.1f);
    }

} // namespace tdg::core
