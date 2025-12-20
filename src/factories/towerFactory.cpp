#include "core/factories/towerFactory.hpp"

#include "core/towers/gatling.hpp"
#include "core/towers/mortar.hpp"
#include "core/towers/laser.hpp"

namespace tdg::core {
    
    TowerPtr TowerFactory::create(Tower::Type type, int x, int y) const {
        switch (type) {
            case Tower::Type::Gatling: return std::make_unique<Gatling>(x, y, getCost(type));
            case Tower::Type::Mortar:  return std::make_unique<Mortar>(x, y, getCost(type));
            case Tower::Type::Laser:   return std::make_unique<Laser>(x, y, getCost(type));
        }
        return nullptr;
    }

    Materials TowerFactory::getCost(Tower::Type type) noexcept {
        switch (type) {
            case Tower::Type::Gatling: return Materials(0u,  0u,  50u);
            case Tower::Type::Mortar:  return Materials(0u,  0u,  75u);
            case Tower::Type::Laser:   return Materials(0u, 10u, 100u);
        }
        return Materials(0,0,0);
    }

} // namespace tdg::core
