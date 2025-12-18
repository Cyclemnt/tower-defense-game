#include "core/factories/vfxManager.hpp"
#include "core/vfxs/gatlingTracerVFX.hpp"
#include "core/vfxs/laserBeamVFX.hpp"
#include "core/vfxs/explosionVFX.hpp"
#include "core/vfxs/hitSparkVFX.hpp"

namespace tdg::core {

    VFXManager::VFXManager(std::queue<Events::VFX>& vxfEvents)
        : m_vfxEvents(vxfEvents) {}

    void VFXManager::renderVideo(IVideoRenderer& vidRenderer) const {
        for (const VFXPtr& v : m_vfxs) v->draw(vidRenderer);
    }

    void VFXManager::update(float dt) {
        clearDeadVFX();
        
        // Create new VFXs
        while (!m_vfxEvents.empty()) {
            Events::VFX& ve = m_vfxEvents.front();
            m_vfxs.push_back(std::move(create(ve)));
            m_vfxEvents.pop();
        }

        // Update VFXs
        for (VFXPtr& v : m_vfxs) v->update(dt);
    }

    void VFXManager::clearDeadVFX() {
        for (auto it = m_vfxs.begin(); it != m_vfxs.end();) {
            VFXPtr& v = *it;
            if (!v->isAlive()) it = m_vfxs.erase(it);
            else ++it;
        }
    }
    
    VFXPtr VFXManager::create(Events::VFX& data) const {
        switch (data.type) {
            case Events::VFX::Type::GatlingTracer: return std::make_unique<GatlingTracerVFX>(data.level, data.xStart, data.yStart, data.xEnd.value(), data.yEnd.value());
            case Events::VFX::Type::LaserBeam:     return std::make_unique<LaserBeamVFX>(data.level, data.xStart, data.yStart, data.xEnd.value(), data.yEnd.value());
            case Events::VFX::Type::Explosion:     return std::make_unique<ExplosionVFX>(data.level, data.xStart, data.yStart);
            case Events::VFX::Type::HitSpark:      return std::make_unique<HitSparkVFX>(data.level, data.xStart, data.yStart);
        }
        return nullptr;
    }

} // namespace tdg::core
