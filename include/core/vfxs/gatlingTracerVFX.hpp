#ifndef GATLING_TRACER_VFX_HPP
#define GATLING_TRACER_VFX_HPP

#include "core/vfxs/vfx.hpp"

namespace tdg::core {

    class GatlingTracerVFX final : public VFX {
    public:
        GatlingTracerVFX(unsigned int level, float x1, float y1, float x2, float y2);

        void draw(IVideoRenderer& vidRenderer) const override;

    private:
        float m_jitterX{0.0f}, m_jitterY{0.0f};
        float m_x2{0.0f}, m_y2{0.0f};

        void randomizeColor();
        void randomizeJitter();
    };

} // namespace tdg::core

#endif // GATLING_TRACER_VFX_HPP
