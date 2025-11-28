#include "core/creatures/minion.hpp"

namespace tdg::core {

    Minion::Minion(bool boosted) noexcept
        : Creature({
            /* health */ boosted ? 125.0f : 25.0f,
            /* shield */ 0.0f,
            /* speed */ 1.0f,
            /* coresCapacity */ 1u,
            /* loot */ {
                0u,                     // Au (gold)
                boosted ? 5u : 1u,      // Ag (silver)
                boosted ? 10u : 5u      // Cu (copper)
            },
            boosted
        }) {}
    
} // namespace tdg::core
