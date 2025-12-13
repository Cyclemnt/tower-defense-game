#include "core/creatures/minion.hpp"

namespace tdg::core {

    Minion::Minion(bool boosted) noexcept
        : Creature({
            /* health */ boosted ? 125.0f : 25.0f,
            /* shield */ 0.0f,
            /* speed */ 1.0f,
            /* coresCapacity */ 1u,
            /* loot */ {
                0u,                     // Au
                boosted ? 5u : 1u,      // Ag
                boosted ? 10u : 5u      // Cu
            },
            boosted
        }) {}

    std::string Minion::spriteId() const noexcept {
        unsigned int frame = m_tick / 8 % 4;
        return m_stats.boosted
            ? "creature_minion_b_" + std::to_string(frame)
            : "creature_minion_" + std::to_string(frame);
    }
    
} // namespace tdg::core
