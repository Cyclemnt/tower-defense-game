#include "../../include/creatures/tank.hpp"

Tank::Tank(bool boosted_) noexcept
    : Creature(
        /* health */ boosted_ ? 150.f : 125.f,
        /* shield */ boosted_ ? 300.f : 75.f,
        /* speed */ 0.25f,
        /* coresCapacity */ 3u,
        /* loot */ {
            1u,                    // Au
            2u,                    // Ag
            boosted_ ? 40u : 10u   // Cu
        },
        boosted_
    ) {}

std::string Tank::getTextureName(const int frame) const {
    return boosted
        ? "creature_tank_b_" + std::to_string(frame) + ".png"
        : "creature_tank_"   + std::to_string(frame) + ".png";
}
