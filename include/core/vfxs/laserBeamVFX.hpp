#ifndef LASER_BEAM_VFX_HPP
#define LASER_BEAM_VFX_HPP

#include "core/vfxs/vfx.hpp"

namespace tdg::core {

    class LaserBeamVFX final : public VFX {
    public:
        LaserBeamVFX(unsigned int level, float x1, float y1, float x2, float y2);
    };

} // namespace tdg::core

#endif // LASER_BEAM_VFX_HPP