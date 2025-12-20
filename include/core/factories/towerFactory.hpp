#ifndef TOWER_FACTORY_HPP
#define TOWER_FACTORY_HPP

#include <memory>
#include "core/towers/tower.hpp"

namespace tdg::core { class Materials; };

namespace tdg::core {
    
    class TowerFactory {
    public:
        TowerPtr create(Tower::Type type, int x, int y) const;
        static Materials getCost(Tower::Type type) noexcept;
    };

} // namespace tdg::core


#endif // TOWER_FACTORY_HPP