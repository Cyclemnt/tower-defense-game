#include "../../include/towers/tower.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

Tower::Tower(int x_, int y_, int au, int ag, int cu, int dmg, float rng, float rate)
    : x(x_), y(y_), priceAu(au), priceAg(ag), priceCu(cu), damage(dmg), range(rng), fireRate(rate), level(1), cooldown(0.0f), target(nullptr) {}

int Tower::getX() const { return x; }

int Tower::getY() const { return y; }

int Tower::getLevel() const { return level; }

float Tower::getDamage() const { return damage; }

float Tower::getRange() const { return range; }

float Tower::getFireRate() const { return fireRate; }

std::array<int, 3> Tower::getPrice() const { return {priceAu, priceAg, priceCu}; }

void Tower::update(float deltaTime, const std::vector<std::unique_ptr<Creature>>& creatures) {
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

    // Attack while cooldown let it
    while (target && cooldown <= 0.0f) {
        attack(target);
        cooldown += 1.0f / (fireRate); // seconds
    }
}

void Tower::attack(Creature* target) {
    if (!target || !target->isAlive()) return;
    target->takeDamage(damage);
}

Creature* Tower::selectTarget(const std::vector<std::unique_ptr<Creature>>& creatures) {
    Creature* best = nullptr;
    float closest = std::numeric_limits<float>::max();

    for (auto& c : creatures) {
        if (!c->isAlive()) continue;

        float dx = c->getPosition()[0] - x;
        float dy = c->getPosition()[1] - y;
        float dist = std::sqrt(dx*dx + dy*dy);

        if (dist <= range) {
            if (!best) best = c.get();
            else {
                // Selecting the closest
                if (dist < closest) {
                    best = c.get();
                    closest = dist;
                }
            }
        }
    }

    return best;
}

void Tower::upgrade() {
    level++;
    damage = static_cast<int>(damage * 1.5f);
    range += 1.0f;
    fireRate *= 1.2f;
}
