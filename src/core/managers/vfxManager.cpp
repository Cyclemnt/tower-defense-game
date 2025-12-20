#include "core/managers/vfxManager.hpp"

#include "core/events.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

namespace tdg::core {

    VFXManager::VFXManager() {}

    void VFXManager::renderVideo(IVideoRenderer& vidRenderer) const {
        for (const VFXPtr& v : m_vfxs) v->draw(vidRenderer);
    }

    void VFXManager::update(float dt, Events& events) {
        clearDeadVFX();
        
        // Create new VFXs
        while (!events.vfxs.empty()) {
            Events::NewVFX& event = events.vfxs.front();
            m_vfxs.push_back(std::move(m_factory.create(event)));
            events.vfxs.pop();
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

} // namespace tdg::core
