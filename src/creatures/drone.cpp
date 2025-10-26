#include "../../include/creatures/drone.hpp"

Drone::Drone(bool boosted_) noexcept
    : Creature(
        /* health */ boosted_ ? 125.f : 75.f,
        /* shield */ boosted_ ? 100.f : 25.f,
        /* speed */ boosted_ ? 0.7f : 0.4f,
        /* coresCapacity */ 2u,
        /* loot */ {
            0u,                     // Au
            boosted_ ? 5u : 0u,     // Ag
            boosted_ ? 40u : 10u    // Cu
        },
        boosted_
    ) {}

std::string Drone::getTextureName(const int frame) const {
    return boosted
        ? "creature_drone_b_" + std::to_string(frame) + ".png"
        : "creature_drone_"   + std::to_string(frame) + ".png";
}
