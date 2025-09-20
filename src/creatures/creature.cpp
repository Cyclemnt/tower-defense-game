#include "../../include/creatures/creature.hpp"

Creature::Creature(int hp, int sh, float spd)
    : health(hp), shield(sh), speed(spd), coresCarried(0),
      pathIndex(0), alive(true) {}

bool Creature::isAlive() const { return alive; }

int Creature::getHealth() const { return health; }

int Creature::getShield() const { return shield; }

int Creature::getCoresCarried() const { return coresCarried; }

void Creature::setPath(const std::vector<Tile*>& p) {
    path = p;
    pathIndex = 0;
}

Tile* Creature::getCurrentTile() const {
    if (path.empty() || pathIndex >= (int)path.size()) return nullptr;
    return path[pathIndex];
}

Tile* Creature::getNextTile() const {
    if (path.empty() || pathIndex + 1 >= (int)path.size()) return nullptr;
    return path[pathIndex + 1];
}

void Creature::update() {
    if (!alive || path.empty()) return;

    // Simple movement: one tile per update (to improve later with speed/ticks)
    if (pathIndex + 1 < (int)path.size()) {
        pathIndex++;
    }
}

void Creature::takeDamage(int dmg) {
    if (!alive) return;

    int remaining = dmg;

    // Shield absorbs first
    if (shield > 0) {
        int absorbed = std::min(shield, remaining);
        shield -= absorbed;
        remaining -= absorbed;
    }

    // Then health
    if (remaining > 0) {
        health -= remaining;
        if (health <= 0) {
            alive = false;
        }
    }
}

void Creature::stealCore() {
    coresCarried++;
}

int Creature::dropCores() {
    int dropped = coresCarried;
    coresCarried = 0;
    return dropped;
}

std::string Creature::getTypeName() const { return "Creature"; }