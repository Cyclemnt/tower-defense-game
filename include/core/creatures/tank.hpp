#ifndef TANK_HPP
#define TANK_HPP

#include "core/creatures/creature.hpp"

namespace tdg::core {
    
    class Tank final : public Creature {
    public:
        explicit Tank(unsigned int level = 1u) noexcept;
        ~Tank() override = default;

        std::string spriteId() const noexcept override;
    };

} // namespace tdg::core

#endif // TANK_HPP