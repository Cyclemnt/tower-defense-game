#include "core/creatures/drone.hpp"

namespace tdg::core {

    Drone::Drone(unsigned int level) noexcept
        : Creature({
            /* health */ level == 2u ? 125.0f : 75.0f,
            /* shield */ level == 2u ? 100.0f : 25.0f,
            /* speed */ level == 2u ? 0.7f : 0.4f,
            /* coresCapacity */ 2u,
            /* loot */ {
                0u,                     // Au
                level == 2u ? 5u : 0u,  // Ag
                level == 2u ? 40u : 10u // Cu
            },
            level
        }) {}

    std::string Drone::spriteId() const noexcept {
        unsigned int frame = m_tick / 8 % 4;
        return "creatures/drone_" + std::to_string(m_stats.level) + "_" + std::to_string(frame);
    }

} // namespace tdg::core
