#ifndef MINION_HPP
#define MINION_HPP

#include "core/creatures/creature.hpp"

namespace tdg::core {
    
    class Minion final : public Creature {
    public:
        explicit Minion(bool boosted = false) noexcept;
        ~Minion() override = default;
    };

} // namespace tdg::core

#endif // MINION_HPP