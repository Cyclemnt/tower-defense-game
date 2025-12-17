#include "core/factories/vfxFactory.hpp"
#include "core/vfxs/gatlingTracerVFX.hpp"
#include "core/vfxs/laserBeamVFX.hpp"
#include "core/vfxs/explosionVFX.hpp"
#include "core/vfxs/hitSparkVFX.hpp"

namespace tdg::core {
    
    VFXPtr VFXFactory::create(Events::VFX& data) const {
        switch (data.type) {
            case Events::VFX::Type::GatlingTracer: return std::make_unique<GatlingTracerVFX>(data.level, data.xStart, data.yStart, data.xEnd.value(), data.yEnd.value());
            case Events::VFX::Type::LaserBeam:     return std::make_unique<LaserBeamVFX>(data.level, data.xStart, data.yStart, data.xEnd.value(), data.yEnd.value());
            case Events::VFX::Type::Explosion:     return std::make_unique<ExplosionVFX>(data.level, data.xStart, data.yStart);
            case Events::VFX::Type::HitSpark:      return std::make_unique<HitSparkVFX>(data.level, data.xStart, data.yStart);
        }
        return nullptr;
    }

} // namespace tdg::core
