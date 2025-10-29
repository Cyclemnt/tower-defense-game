#include "../../include/creatures/minion.hpp"

Minion::Minion(bool boosted_) noexcept
    : Creature(
        /* health */ boosted_ ? 125.0f : 25.0f,
        /* shield */ 0.0f,
        /* speed */ 1.0f,
        /* coresCapacity */ 1u,
        /* loot */ {
            0u,                     // Au (gold)
            boosted_ ? 5u : 1u,     // Ag (silver)
            boosted_ ? 10u : 5u     // Cu (copper)
        },
        boosted_
    ) {}

std::string Minion::getTextureName(const int frame) const {
    return boosted
        ? "creature_minion_b_" + std::to_string(frame) + ".png"
        : "creature_minion_"   + std::to_string(frame) + ".png";
}
