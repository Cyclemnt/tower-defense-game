#ifndef PIPOU_VFX_HPP
#define PIPOU_VFX_HPP

#include "core/vfxs/vfx.hpp"

namespace tdg::core {
    
    class PipouVFX final : public VFX {
    public:
        PipouVFX(float x1, float y1);

        void update(float dt) override; // Updates the time to live and opacity of the effect

        void draw(IVideoRenderer& vidRenderer) const override; // Draws the effet
    
    private:
        void computeFade();
        void randomizePosition(float dt);
        
    float m_time{0.0f};

        float m_speed{2.1};

        float m_lifetime{60.0f};
        float m_fadeDuration{5.0f};
        unsigned int m_alpha{0u};
        unsigned long m_tick{0u};
    };

} // namespace tdg::core

#endif // PIPOU_VFX_HPP