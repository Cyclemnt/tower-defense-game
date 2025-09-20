#include "../../include/towers/tower.hpp"
#include <cmath>
#include <algorithm>

Tower::Tower(int x_, int y_, int au, int ag, int cu,
             int dmg, float rng, float rate, bool area)
    : x(x_), y(y_), priceAu(au), priceAg(ag), priceCu(cu),
      damage(dmg), range(rng), fireRate(rate), areaDamage(area),
      level(1), cooldown(0.0f) {}

void Tower::update(std::vector<Creature*>& creatures) {
    if (cooldown > 0.0f) {
        cooldown -= 1.0f; // 1 tick = 1 unité de temps
        return;
    }

    // Searching a target within range
    Creature* target = nullptr;
    for (Creature* c : creatures) {
        if (!c->isAlive()) continue;

        int dx = c->getCurrentTile()->getX() - x;
        int dy = c->getCurrentTile()->getY() - y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist <= range) {
            target = c;
            break; // simple: shoot the first target found
            // TODO (maybe): use spacial hashing to compute targets faster 
        }
    }

    if (target) {
        attack(target);
        cooldown = 1.0f / fireRate; // reset cooldown
        // TODO: calculate cooldown in ticks/frames
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
