#include "core/creatures/tank.hpp"

namespace tdg::core {

    Tank::Tank(bool boosted) noexcept
        : Creature({
            /* health */ boosted ? 150.0f : 125.0f,
            /* shield */ boosted ? 300.0f : 75.0f,
            /* speed */ 0.25f,
            /* coresCapacity */ 3u,
            /* loot */ {
                1u,                     // Au
                2u,                     // Ag
                boosted ? 40u : 10u     // Cu
            },
            boosted
        }) {}
    
} // namespace tdg::core
