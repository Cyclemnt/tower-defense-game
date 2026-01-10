#ifndef TUMBLEWEED_VFX_HPP
#define TUMBLEWEED_VFX_HPP

#include "core/vfxs/vfx.hpp"

namespace tdg::core {
    
    class TumbleweedVFX final : public VFX {
    public:
        TumbleweedVFX(float x1, float y1);

        void update(float dt) override; // Updates the time to live and opacity of the effect

        void draw(IVideoRenderer& vidRenderer) const override; // Draws the effet
    
    private:
        void computeFade();
        void randomizePosition(float dt);
        
        float m_speed{1.8};

        float m_lifetime{60.0f};
        float m_fadeDuration{5.0f};
        unsigned int m_alpha{0u};
        unsigned long m_tick{0u};
    };

} // namespace tdg::core

#endif // TUMBLEWEED_VFX_HPP