#ifndef BUTTERFLY_VFX_HPP
#define BUTTERFLY_VFX_HPP

#include "core/vfxs/vfx.hpp"

namespace tdg::core {
    
    class ButterflyVFX final : public VFX {
    public:
        ButterflyVFX(float x1, float y1);

        void update(float dt) override; // Updates the time to live and opacity ot the effect

        void draw(IVideoRenderer& vidRenderer) const override; // Draws the effet
    
    private:
        void computeFade();
        void randomizePosition(float dt);

        float m_lifetime{60.0f};
        float m_fadeDuration{5.0f};
        unsigned int m_alpha{0u};
    };

} // namespace tdg::core

#endif // BUTTERFLY_VFX_HPP