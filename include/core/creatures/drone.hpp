#ifndef DRONE_HPP
#define DRONE_HPP

#include "core/creatures/creature.hpp"

namespace tdg::core {
    
    class Drone final : public Creature {
    public:
        explicit Drone(bool boosted = false) noexcept;
        ~Drone() override = default;
    };
    
} // namespace tdg::core

#endif // DRONE_HPP