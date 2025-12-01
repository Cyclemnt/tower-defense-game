#ifndef TOWER_FACTORY_HPP
#define TOWER_FACTORY_HPP

#include "core/towers/tower.hpp"

namespace tdg::core {
    
    class TowerFactory {
    public:
        TowerPtr build(Tower::Type type, int x, int y);
    };

} // namespace tdg::core

#endif // TOWER_FACTORY_HPP