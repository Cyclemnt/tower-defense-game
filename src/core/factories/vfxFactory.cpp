#include "core/factories/vfxFactory.hpp"

#include "core/vfxs/gatlingTracerVFX.hpp"
#include "core/vfxs/laserBeamVFX.hpp"
#include "core/vfxs/explosionVFX.hpp"
#include "core/vfxs/hitSparkVFX.hpp"
#include "core/vfxs/fanucVFX.hpp"
#include "core/vfxs/fireflyVFX.hpp"
#include "core/vfxs/butterflyVFX.hpp"
#include "core/vfxs/pipouVFX.hpp"
#include "core/vfxs/tumbleweedVFX.hpp"

namespace tdg::core {
    
    VFXPtr VFXFactory::create(Events::NewVFX& data) const {
        switch (data.type) {
            case Events::NewVFX::Type::GatlingTracer: return std::make_unique<GatlingTracerVFX>(data.level, data.xStart, data.yStart, data.xEnd.value(), data.yEnd.value());
            case Events::NewVFX::Type::LaserBeam:     return std::make_unique<LaserBeamVFX>(data.level, data.xStart, data.yStart, data.xEnd.value(), data.yEnd.value());
            case Events::NewVFX::Type::Explosion:     return std::make_unique<ExplosionVFX>(data.level, data.xStart, data.yStart);
            case Events::NewVFX::Type::HitSpark:      return std::make_unique<HitSparkVFX>(data.level, data.xStart, data.yStart);
            case Events::NewVFX::Type::Fanuc:         return std::make_unique<FanucVFX>(data.xStart, data.yStart);
            case Events::NewVFX::Type::FireFly:       return std::make_unique<FireflyVFX>(data.xStart, data.yStart);
            case Events::NewVFX::Type::Butterfly:     return std::make_unique<ButterflyVFX>(data.xStart, data.yStart);
            case Events::NewVFX::Type::Pipou:         return std::make_unique<PipouVFX>(data.xStart, data.yStart);
            case Events::NewVFX::Type::Tumbleweed:    return std::make_unique<TumbleweedVFX>(data.xStart, data.yStart);
        }
        return nullptr;
    }

} // namespace tdg::core
