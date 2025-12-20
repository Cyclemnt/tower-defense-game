#ifndef CREATURE_FACTORY_HPP
#define CREATURE_FACTORY_HPP

#include <memory>
#include "core/creatures/creature.hpp"

namespace tdg::core {
    
    class CreatureFactory {
    public:
        CreaturePtr create(Creature::Type type, unsigned int level) const;
    };

} // namespace tdg::core

#endif // CREATURE_FACTORY_HPP