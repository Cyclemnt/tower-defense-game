#include <cmath>
#include "../../include/towers/laser.hpp"
#include "../../include/creatures/creature.hpp"
#include "../../include/visual-effects/laserEffect.hpp"

Laser::Laser(sf::Vector2i position_) noexcept
    : Tower(position_,
        /* cost */ {
            0u,     // Au
            10u,    // Ag
            100u    // Cu
        },
        /*dmg*/ 0.1f,
        /*rng*/ 3.0f,
        /*rate*/ 15.0f
    ), damageScale(1.0f), baseDamage(0.1f) {}

void Laser::update(float deltaTime, const std::vector<std::unique_ptr<Creature>>& creatures) {
    if (target || cooldown > 0.0f)
        cooldown -= deltaTime;

    // Validate target
    if (target && (!target->isAlive() || distance(sf::Vector2f(position), target->getPosition()) > range)) {
        clearTarget();
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
        // Create Laser Beam
        visualEffects.push_back(std::make_unique<LaserEffect>(sf::Vector2f(position), target->getPosition()));
    }

    // Acquire new target if needed
    else if (!target) {
        if (cooldown < 0.0f)
            cooldown = 0.0f;  // Cooldown cannot be negative when target is lost
        target = selectTarget(creatures);
        lockTime = 0.0f;
    }

    // Attack while cooldown allows
    while (target && cooldown <= 0.0f) {
        attack(target);
        cooldown += 1.0f / (fireRate); // seconds
    }
}

std::string Laser::getTextureName(int frame) const {
    return "tower_laser_" + std::to_string(frame) + ".png";
}
