#include "core/factories/creatureFactory.hpp"
#include "core/creatures/drone.hpp"
#include "core/creatures/minion.hpp"
#include "core/creatures/tank.hpp"

namespace tdg::core {

    CreaturePtr CreatureFactory::create(Creature::Type type) {
        switch (type) {
            case Creature::Type::Drone: return std::make_unique<Drone>();
            case Creature::Type::Minion: return std::make_unique<Minion>();
            case Creature::Type::Tank: return std::make_unique<Tank>();
            
            case Creature::Type::DroneB: return std::make_unique<Drone>(true);
            case Creature::Type::MinionB: return std::make_unique<Minion>(true);
            case Creature::Type::TankB: return std::make_unique<Tank>(true);
        }

        return nullptr;
    }

} // nameapace tdg::core
