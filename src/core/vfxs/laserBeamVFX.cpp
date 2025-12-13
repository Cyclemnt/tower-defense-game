#include "core/vfxs/laserBeamVFX.hpp"

namespace tdg::core {
    
    LaserBeamVFX::LaserBeamVFX(unsigned int level, float x1, float y1, float x2, float y2)
        : VFX(level, x1, y1, x2, y2)
    {
        // setColor(255u, 120u, 30u, 255u);
        switch (level) {
            case 1u: setColor(255u, 234u, 55u, 0u); break;
            case 2u: setColor(255u, 177u, 32u, 0u); break;
            case 3u: setColor(255u, 64u, 20u, 0u); break;
            
            default: break;
        }
    }

} // namespace tdg::core
