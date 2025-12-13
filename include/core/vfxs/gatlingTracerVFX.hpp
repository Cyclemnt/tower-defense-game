#ifndef GATLING_TRACER_VFX_HPP
#define GATLING_TRACER_VFX_HPP

#include "core/vfxs/vfx.hpp"

namespace tdg::core {

    class GatlingTracerVFX final : public VFX {
    private:
        float m_jitterX{0.0f}, m_jitterY{0.0f};

        void randomizeColor();
        void randomizeJitter();

    public:
        GatlingTracerVFX(unsigned int level, float x1, float y1, float x2, float y2);
    };

} // namespace tdg::core

#endif // GATLING_TRACER_VFX_HPP
