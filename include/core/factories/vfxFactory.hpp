#ifndef VFX_FACTORY_HPP
#define VFX_FACTORY_HPP

#include "core/vfxs/vfx.hpp"
#include "core/events.hpp"

namespace tdg::core {
    
    class VFXFactory {
    public:
        VFXPtr create(VFXEventData& data);
    };

} // namespace tdg::core


#endif // VFX_FACTORY_HPP