#include "core/creatures/minion.hpp"

namespace tdg::core {

    Minion::Minion(unsigned int level) noexcept
        : Creature({
            /* health */ level == 2u ? 125.0f : 25.0f,
            /* shield */ 0.0f,
            /* speed */ 1.0f,
            /* coresCapacity */ 1u,
            /* loot */ {
                0u,                     // Au
                level == 2u ? 5u : 1u,  // Ag
                level == 2u ? 10u : 5u  // Cu
            },
            level
        }) {}

    std::string Minion::spriteId() const noexcept {
        unsigned int frame = m_tick / 8 % 4;
        return "creatures/minion_" + std::to_string(m_stats.level) + "_" + std::to_string(frame);
    }
    
} // namespace tdg::core
