#ifndef GATLING_TRACER_VFX_HPP
#define GATLING_TRACER_VFX_HPP

#include "core/vfxs/vfx.hpp"

namespace tdg::core {

    class GatlingTracerVFX final : public VFX {
    public:
        GatlingTracerVFX(unsigned int level, float x1, float y1, float x2, float y2);

        virtual float zOrder() const noexcept override { return m_y2; } // Used to sort before rendering (higher : in front of)
        void draw(IVideoRenderer& vidRenderer) const override; // Draws the effect

    private:
        float m_jitterX{0.0f}, m_jitterY{0.0f};
        float m_x2{0.0f}, m_y2{0.0f};

        void randomizeColor(); // Randomizes the color
        void randomizeJitter(); // Randomizes the jitter (small variation of the end point of the effect)
    };

} // namespace tdg::core

#endif // GATLING_TRACER_VFX_HPP
