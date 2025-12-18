#ifndef DRONE_HPP
#define DRONE_HPP

#include "core/creatures/creature.hpp"

namespace tdg::core {
    
    class Drone final : public Creature {
    public:
        explicit Drone(unsigned int level = 1u) noexcept;
        ~Drone() override = default;

        std::string spriteId() const noexcept override;
    };
    
} // namespace tdg::core

#endif // DRONE_HPP