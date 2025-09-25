#include "../../include/towers/tower.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

Tower::Tower(int x_, int y_, int au, int ag, int cu, int dmg, float rng, float rate, bool area)
    : x(x_), y(y_), priceAu(au), priceAg(ag), priceCu(cu), damage(dmg), range(rng), fireRate(rate), areaDamage(area), level(1), cooldown(0.0f), target(nullptr) {}

int Tower::getX() const { return x; }

int Tower::getY() const { return y; }

int Tower::getLevel() const { return level; }

int Tower::getDamage() const { return damage; }

float Tower::getRange() const { return range; }

float Tower::getFireRate() const { return fireRate; }

bool Tower::isAreaDamage() const { return areaDamage; }

std::array<int, 3> Tower::getPrice() const { return {priceAu, priceAg, priceCu}; }

void Tower::update(float deltaTime, std::vector<Creature*>& creatures) {
    std::cout << "twr cooldown: " << cooldown << std::endl;
    cooldown -= deltaTime; // 1 tick = 1 time unit (1 frame)

    // Verify if actual target is still available
    if (target && (!target->isAlive() || std::sqrt(std::pow(target->getPosition()[0] - x, 2) + std::pow(target->getPosition()[1] - y, 2)) > range)) {
        target = nullptr; // Loosing lockdown
    }

    // Selecting new target if required
    if (!target) {
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

    if (areaDamage) {
        // TODO: damage close creatures
        target->takeDamage(damage);
    } else {
        target->takeDamage(damage);
    }
}

Creature* Tower::selectTarget(const std::vector<Creature*>& creatures) {
    Creature* best = nullptr;

    for (Creature* c : creatures) {
        if (!c->isAlive()) continue;

        float dx = c->getPosition()[0] - x;
        float dy = c->getPosition()[1] - y;
        float dist = std::sqrt(dx*dx + dy*dy);

        if (dist <= range) {
            if (!best) best = c;
            else {
                // Selecting highest HP
                if (c->getHealth() > best->getHealth()) {
                    best = c;
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
