#ifndef TANK_HPP
#define TANK_HPP

#include "creature.hpp"

namespace tdg::core {
    
    class Tank final : public Creature {
    public:
        explicit Tank(bool boosted = false) noexcept;
        ~Tank() override = default;
    };

} // namespace tdg::core

#endif // TANK_HPP