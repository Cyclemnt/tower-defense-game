#ifndef LASER_BEAM_VFX_HPP
#define LASER_BEAM_VFX_HPP

#include "core/vfxs/vfx.hpp"

namespace tdg::core {

    class LaserBeamVFX final : public VFX {
    public:
        LaserBeamVFX(unsigned int level, float x1, float y1, float x2, float y2);

        void update(float dt) override; // Updates the time to live and the opacity of the effect

        virtual float zOrder() const noexcept override { return m_y2; } // Used to sort before rendering (higher : in front of)
        void draw(IVideoRenderer& vidRenderer) const override; // Draws the effect
    
    private:
        utils::Color m_glow;
        float m_x2{0.0f}, m_y2{0.0f};
        float m_lifetime{0.0f};
    };

} // namespace tdg::core

#endif // LASER_BEAM_VFX_HPP