#include "core/factories/creatureFactory.hpp"
#include "core/creatures/drone.hpp"
#include "core/creatures/minion.hpp"
#include "core/creatures/tank.hpp"

namespace tdg::core {

    CreaturePtr CreatureFactory::create(Creature::Type type, unsigned int level) const {
        switch (type) {
            case Creature::Type::Drone: return std::make_unique<Drone>(level);
            case Creature::Type::Minion: return std::make_unique<Minion>(level);
            case Creature::Type::Tank: return std::make_unique<Tank>(level);
        }
        return nullptr;
    }

} // nameapace tdg::core
