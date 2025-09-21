#include "../../include/towers/tower.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

Tower::Tower(int x_, int y_, int au, int ag, int cu, int dmg, float rng, float rate, bool area)
    : x(x_), y(y_), priceAu(au), priceAg(ag), priceCu(cu), damage(dmg), range(rng), fireRate(rate), areaDamage(area), level(1), cooldown(0.0f) {}

int Tower::getX() const { return x; }

int Tower::getY() const { return y; }

int Tower::getLevel() const { return level; }

int Tower::getDamage() const { return damage; }

float Tower::getRange() const { return range; }

float Tower::getFireRate() const { return fireRate; }

bool Tower::isAreaDamage() const { return areaDamage; }

std::array<int, 3> Tower::getPrice() const { return {priceAu, priceAg, priceCu}; }

void Tower::update(std::vector<Creature*>& creatures) {
    std::cout << "twr cooldown: " << cooldown << std::endl;
    if (cooldown > 0.0f) {
        cooldown -= std::min(1.0f, cooldown); // 1 tick = 1 unité de temps
        if (cooldown != 0.0f)
            return;
    }

    // Searching a target within range
    Creature* target = nullptr;
    for (Creature* c : creatures) {
        if (!c->isAlive()) continue;

        int dx = c->getCurrentTile()->getX() - x;
        int dy = c->getCurrentTile()->getY() - y;
        float dist = std::sqrt(dx * dx + dy * dy); // Possible optimization by comparing square distance

        if (dist <= range) {
            target = c;
            break; // simple: shoot the first target found, in spawn order
            // TODO (maybe): use spacial hashing to compute targets faster 
        }
    }

    if (target) {
        attack(target);
        cooldown = 1.0f / fireRate; // reset cooldown
        // TODO: calculate cooldown in ticks/frames
        // cooldown = framerate / firerate
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

void Tower::upgrade() {
    level++;
    damage = static_cast<int>(damage * 1.5f);
    range += 1.0f;
    fireRate *= 1.2f;
}
