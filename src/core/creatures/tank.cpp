#include "core/creatures/tank.hpp"

namespace tdg::core {

    Tank::Tank(unsigned int level) noexcept
        : Creature({
            /* health */ level == 2u ? 150.0f : 125.0f,
            /* shield */ level == 2u ? 300.0f : 75.0f,
            /* speed */ 0.25f,
            /* coresCapacity */ 3u,
            /* loot */ {
                1u,                     // Au
                2u,                     // Ag
                level == 2u ? 40u : 10u // Cu
            },
            level
        }) {}

    std::string Tank::spriteId() const noexcept {
        unsigned int frame = m_tick / 8 % 4;
        return "creatures/tank_" + std::to_string(m_stats.level) + "_" + std::to_string(frame);
    }
    
} // namespace tdg::core
