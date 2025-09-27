#include "../../include/towers/laser.hpp"
#include <iostream>
#include <cmath>

Laser::Laser(int x_, int y_)
    : Tower(x_, y_, 0 /*au*/, 10 /*ag*/, 100 /*cu*/, 0.1f /*dmg*/, 3.0f /*rng*/, 15.0f /*rate*/),
    damageScale(1.0f), baseDamage(0.1f) {}

Laser::~Laser() {}

void Laser::update(float deltaTime, std::vector<Creature*>& creatures) {
    std::cout << "twr cooldown: " << cooldown << std::endl;
    if (target || cooldown > 0.0f)
        cooldown -= deltaTime; // 1 tick = 1 time unit (1 frame)

    // Verify if actual target is still available
    if (target && (!target->isAlive() || std::sqrt(std::pow(target->getPosition()[0] - x, 2) + std::pow(target->getPosition()[1] - y, 2)) > range)) {
        target = nullptr; // Loosing lockdown
        // Reset damage scale over time
        lockTime = 0.0f; // Reset lock timer
        damageScale = 1.0f; // Reset damage coefficient
        damage = baseDamage; // Reset damage
    }

    // Update damage scale over time
    if (target) {
        lockTime += deltaTime;
        damageScale = 2.9f * std::min(lockTime, 10.0f) + 1.0; // Scales from 1x at 0s to 30x at 10s: ((maxScale-minScale)/maxTime * min(time, maxTime) + 1)
        damage = baseDamage * damageScale;
        std::cout << "Laser damage: " << damage << "\n";
    }

    // Selecting new target if required
    if (!target) {
        if (cooldown < 0.0f)
            cooldown = 0.0f;  // Cooldown cannot be negative when target is lost
        target = selectTarget(creatures);
    }

    // Attack while cooldown let it
    while (target && cooldown <= 0.0f) {
        attack(target);
        cooldown += 1.0f / (fireRate); // seconds
    }
}

std::string Laser::getTypeName() const { return "Laser"; }
