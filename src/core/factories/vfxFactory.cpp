#include "core/factories/vfxFactory.hpp"
#include "core/vfxs/gatlingTracerVFX.hpp"
#include "core/vfxs/laserBeamVFX.hpp"
#include "core/vfxs/explosionVFX.hpp"
#include "core/vfxs/hitSparkVFX.hpp"

namespace tdg::core {
    
    VFXPtr VFXFactory::create(VFXEventData& data) {
        switch (data.type) {
            case VFXType::GatlingTracer: return std::make_unique<GatlingTracerVFX>(data.level, data.xStart, data.yStart, data.xEnd.value(), data.yEnd.value());
            case VFXType::LaserBeam:     return std::make_unique<LaserBeamVFX>(data.level, data.xStart, data.yStart, data.xEnd.value(), data.yEnd.value());
            case VFXType::Explosion:     return std::make_unique<ExplosionVFX>(data.level, data.xStart, data.yStart);
            case VFXType::HitSpark:      return std::make_unique<HitSparkVFX>(data.level, data.xStart, data.yStart);
        }
        return nullptr;
    }

} // namespace tdg::core
