#ifndef CREATURE_FACTORY_HPP
#define CREATURE_FACTORY_HPP

#include "core/creatures/creature.hpp"

namespace tdg::core {
    
    class CreatureFactory {
    public:
        CreaturePtr create(Creature::Type type);
    };

} // namespace tdg::core

#endif // CREATURE_FACTORY_HPP