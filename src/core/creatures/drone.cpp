#include "core/creatures/drone.hpp"

namespace tdg::core {

    Drone::Drone(bool boosted) noexcept
        : Creature({
            /* health */ boosted ? 125.0f : 75.0f,
            /* shield */ boosted ? 100.0f : 25.0f,
            /* speed */ boosted ? 0.7f : 0.4f,
            /* coresCapacity */ 2u,
            /* loot */ {
                0u,                     // Au
                boosted ? 5u : 0u,      // Ag
                boosted ? 40u : 10u     // Cu
            },
            boosted
        }) {}

} // namespace tdg::core
