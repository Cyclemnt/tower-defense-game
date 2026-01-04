#include "core/factories/creatureFactory.hpp"

#include "core/creatures/drone.hpp"
#include "core/creatures/minion.hpp"
#include "core/creatures/tank.hpp"
#include "core/creatures/mother.hpp"

namespace tdg::core {
    
    CreaturePtr CreatureFactory::create(Creature::Type type, unsigned int level) const {
        switch (type) {
            case Creature::Type::Drone: return std::make_shared<Drone>(level);
            case Creature::Type::Minion: return std::make_shared<Minion>(level);
            case Creature::Type::Tank: return std::make_shared<Tank>(level);
            case Creature::Type::Mother: return std::make_shared<Mother>(level);
        }
        return nullptr;
    }

} // namespace tdg::core
