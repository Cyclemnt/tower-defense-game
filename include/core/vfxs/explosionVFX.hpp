#ifndef EXPLOSION_VFX_HPP
#define EXPLOSION_VFX_HPP

#include "core/vfxs/vfx.hpp"

namespace tdg::core {
    
    class ExplosionVFX final : public VFX {
    public:
        ExplosionVFX(unsigned int level, float x1, float y1);

        void update(float dt) override;

        void draw(IVideoRenderer& vidRenderer) const override;

    private:
        const float m_lifetime{0.3f};
        const float m_maxRadius{0.4f};
        float m_radius{0.0f};
        Color m_glow;
    };

} // namespace tdg::core

#endif // EXPLOSION_VFX_HPP