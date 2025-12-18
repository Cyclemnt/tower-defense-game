#ifndef VFX_FACTORY_HPP
#define VFX_FACTORY_HPP

#include "core/events.hpp"
#include "core/interfaces/iVideoRenderer.hpp"
#include "core/vfxs/vfx.hpp"

namespace tdg::core {
    
    class VFXManager {
    public:
        VFXManager(std::queue<Events::VFX>& vxfEvents);
        void renderVideo(IVideoRenderer& vidRenderer) const; // Draws every VFX

        void update(float dt); // Main function to create new VFXs and update them
        void clearDeadVFX();
        
        VFXPtr create(Events::VFX& data) const; // VFX Factory

    private:
        std::queue<Events::VFX>& m_vfxEvents;
        std::vector<VFXPtr> m_vfxs;
    };

} // namespace tdg::core


#endif // VFX_FACTORY_HPP