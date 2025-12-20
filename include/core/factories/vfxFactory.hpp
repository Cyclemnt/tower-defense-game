#ifndef VFX_FACTORY_HPP
#define VFX_FACTORY_HPP

#include <memory>
#include "core/vfxs/vfx.hpp"
#include "core/events.hpp"

namespace tdg::core {
    
    class VFXFactory {
    public:
        VFXPtr create(Events::NewVFX& data) const;
    };

} // namespace tdg::core

#endif // VFX_FACTORY_HPP