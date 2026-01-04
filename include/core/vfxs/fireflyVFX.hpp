#ifndef FIREFLY_VFX_HPP
#define FIREFLY_VFX_HPP

#include "core/vfxs/vfx.hpp"

namespace tdg::core {
    
    class FireflyVFX final : public VFX {
    public:
        FireflyVFX(float x1, float y1);

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

#endif // FIREFLY_VFX_HPP