#include "core/factories/towerFactory.hpp"
#include "core/towers/gatling.hpp"
#include "core/towers/mortar.hpp"
#include "core/towers/laser.hpp"

namespace tdg::core {
    
    TowerPtr TowerFactory::build(Tower::Type type, int x, int y) const {
        switch (type) {
            case Tower::Type::Gatling: return std::make_unique<Gatling>(x, y);
            case Tower::Type::Mortar:  return std::make_unique<Mortar>(x, y);
            case Tower::Type::Laser:   return std::make_unique<Laser>(x, y);
        }
        return nullptr;
    }

} // namespace tdg::core
