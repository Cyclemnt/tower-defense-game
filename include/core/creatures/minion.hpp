#ifndef MINION_HPP
#define MINION_HPP

#include "core/creatures/creature.hpp"

namespace tdg::core {
    
    class Minion final : public Creature {
    public:
        explicit Minion(unsigned int level = 1u) noexcept;
        ~Minion() override = default;

        std::string spriteId() const noexcept override;
    };

} // namespace tdg::core

#endif // MINION_HPP