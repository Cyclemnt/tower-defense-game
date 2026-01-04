#ifndef FANUC_VFX_HPP
#define FANUC_VFX_HPP

#include "core/vfxs/vfx.hpp"

namespace tdg::core {
    
    class FanucVFX final : public VFX {
    public:
        FanucVFX(float x1, float y1);

        void update(float dt) override; // Updates the time to live and opacity ot the effect

        void draw(IVideoRenderer& vidRenderer) const override; // Draws the effet
    
    private:
        void computeFade();

        float m_lifetime{120.0f};
        float m_fadeDuration{5.0f};
        unsigned int m_alpha{0u};
        unsigned long m_tick{0u};
    };

} // namespace tdg::core

#endif // FANUC_VFX_HPP