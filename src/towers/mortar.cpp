#include <cmath>
#include "../../include/towers/mortar.hpp"
#include "../../include/creatures/creature.hpp"
#include "../../include/visual-effects/explosionEffect.hpp"
#include "../../include/visual-effects/shellEffect.hpp"
#include "../../include/visual-effects/visualEffect.hpp"

Mortar::Mortar(int x_, int y_)
                 : Tower(x_, y_, 0 /*au*/, 0 /*ag*/, 75 /*cu*/, 48 /*dmg*/, 4.0f /*rng*/, 0.333333f /*rate*/) {}

Mortar::~Mortar() {}

const std::vector<Shell>& Mortar::getShells() const { return shells; }

void Mortar::update(float deltaTime, const std::vector<std::unique_ptr<Creature>>& creatures) {
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
        if (dist < s.speed * deltaTime) {
            // Impact
            for (auto& c : creatures) {
                float dx = c->getPosition()[0] - s.targetX;
                float dy = c->getPosition()[1] - s.targetY;
                float distSquare = dx*dx + dy*dy;
                float damageCoefficient = std::exp(-distSquare/(s.explosionRadius * s.explosionRadius / 4.0f)); // Gaussian distribution
                if (distSquare < s.explosionRadius * s.explosionRadius)
                    c->takeDamage(damage * damageCoefficient);
            }
            std::array<float, 2> pos = {s.posX, s.posY};
            visualEffects.push_back(std::make_unique<ExplosionEffect>(pos)); // Create explosion effect
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
        std::array<float, 2> pos = {s.posX, s.posY}, target = {s.targetX, s.targetY};
        visualEffects.push_back(std::make_unique<ShellEffect>(pos, target, s.speed));
        cooldown += 1.0f / (fireRate); // seconds
    }
}

std::string Mortar::getTypeName() const { return "Mortar"; }
