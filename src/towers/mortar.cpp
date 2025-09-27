#include "../../include/towers/mortar.hpp"
#include <iostream>
#include <cmath>

Mortar::Mortar(int x_, int y_)
                 : Tower(x_, y_, 0 /*au*/, 0 /*ag*/, 75 /*cu*/, 48 /*dmg*/, 4.0f /*rng*/, 0.333333f /*rate*/) {}

Mortar::~Mortar() {}

void Mortar::update(float deltaTime, std::vector<Creature*>& creatures) {
    std::cout << "twr cooldown: " << cooldown << std::endl;
    if (target || cooldown > 0.0f)
        cooldown -= deltaTime; // 1 tick = 1 time unit (1 frame)

    // Verify if actual target is still available
    if (target && (!target->isAlive() || std::sqrt(std::pow(target->getPosition()[0] - x, 2) + std::pow(target->getPosition()[1] - y, 2)) > range)) {
        target = nullptr; // Loosing lockdown
    }

    // Selecting new target if required
    if (!target) {
        if (cooldown < 0.0f)
            cooldown = 0.0f;  // Cooldown cannot be negative when target is lost
        target = selectTarget(creatures);
    }

    // Update projectiles
    for (auto it = shells.begin(); it != shells.end(); ) {
        Shell& s = *it;  // Get the element

        float dx = s.targetX - s.posX;
        float dy = s.targetY - s.posY;
        float dist = std::sqrt(dx*dx + dy*dy);
        std::cout << "shell dist: " << dist << "\n";
        if (dist < s.speed * deltaTime) {
            // Impact
            std::cout << "Shell exploding" << "\n";
            for (Creature* c : creatures) {
                float dx = c->getPosition()[0] - s.targetX;
                float dy = c->getPosition()[1] - s.targetY;
                float distSquare = dx*dx + dy*dy;
                float damageCoefficient = std::exp(-distSquare/(s.explosionRadius * s.explosionRadius / 4.0f)); // Gaussian distribution
                if (distSquare < s.explosionRadius * s.explosionRadius)
                    c->takeDamage(damage * damageCoefficient);
            }
            it = shells.erase(it);  // Erease element and get new iterator
        } else {
            s.posX += (dx/dist) * s.speed * deltaTime;
            s.posY += (dy/dist) * s.speed * deltaTime;
            ++it;  // If not ereased, go to next element
        }
    }

    
    // Shoot shells while cooldown let it
    while (target && cooldown <= 0.0f) {
        // Create new projectile
        Shell s{(float)x, (float)y, target->getPosition()[0], target->getPosition()[1], damage};
        shells.push_back(s);
        cooldown += 1.0f / (fireRate); // seconds
    }
}

std::string Mortar::getTypeName() const { return "Mortar"; }
