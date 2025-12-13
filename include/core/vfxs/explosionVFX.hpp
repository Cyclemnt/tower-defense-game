#ifndef EXPLOSION_VFX_HPP
#define EXPLOSION_VFX_HPP

#include "core/vfxs/vfx.hpp"

namespace tdg::core {
    
    class ExplosionVFX final : public VFX {
    private:
        float m_maxRadius{0.4f};

    public:
        ExplosionVFX(unsigned int level, float x1, float y1);
    };

} // namespace tdg::core

#endif // EXPLOSION_VFX_HPP