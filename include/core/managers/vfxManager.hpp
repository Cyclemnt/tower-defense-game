#ifndef VFX_MANAGER_HPP
#define VFX_MANAGER_HPP

#include <vector>
#include "core/vfxs/vfx.hpp"
#include "core/factories/vfxFactory.hpp"

namespace tdg::core { class Events; class IVideoRenderer; };

namespace tdg::core {
    
    class VFXManager {
    public:
        VFXManager();
        void renderVideo(IVideoRenderer& vidRenderer) const; // Draws every VFX

        void update(float dt, Events& events); // Main function to create new VFXs and update them
        void clearDeadVFX();

    private:
        VFXFactory m_factory;

        std::vector<VFXPtr> m_vfxs;
    };

} // namespace tdg::core


#endif // VFX_MANAGER_HPP