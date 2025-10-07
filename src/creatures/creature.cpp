#include "../../include/creatures/creature.hpp"
#include "../../include/map/coreStorage.hpp"
#include "../../include/map/exitZone.hpp"
#include <cmath>

Creature::Creature(float hp, float sh, float spd, int coresCapacity_, int au_, int ag_, int cu_)
    : health(hp), shield(sh), speed(spd), coresCapacity(coresCapacity_), au(au_), ag(ag_), cu(cu_), coresCarried(0),
    pathIndex(0), alive(true) {}

bool Creature::isAlive() const { return alive; }

float Creature::getHealth() const { return health; }

float Creature::getShield() const { return shield; }

float Creature::getSpeed() const { return speed; }

int Creature::getCoresCarried() const { return coresCarried; }

std::array<int, 3> Creature::getLoot() const { return {au, ag, cu}; }

void Creature::setPath(const std::vector<Tile*>& p) {
    path = p;
    pathIndex = 0;
}

void Creature::setPosition(std::array<int, 2> pos) {
    posX = pos[0];
    posY = pos[1];
}

std::array<float, 2> Creature::getPosition() const {
    return {posX, posY};
}

Tile* Creature::getCurrentTile() const {
    if (path.empty() || pathIndex >= (int)path.size()) return nullptr;
    return path[pathIndex];
}

Tile* Creature::getNextTile() const {
    if (path.empty() || pathIndex + 1 >= (int)path.size()) return nullptr;
    return path[pathIndex + 1];
}

Tile* Creature::getDestinationTile() const {
    if (path.empty()) return nullptr;
    return path.back();
}

void Creature::update(float deltaTime) {
    if (!alive || path.empty() || pathIndex + 1 >= (int)path.size())
        return;

    float distanceToTravel = speed * deltaTime;

    while (distanceToTravel > 0.0f && pathIndex + 1 < (int)path.size()) {
        Tile* current = path[pathIndex];
        Tile* next = path[pathIndex + 1];

        float targetX = next->getX();
        float targetY = next->getY();

        float dx = targetX - posX;
        float dy = targetY - posY;
        float distToNext = std::sqrt(dx * dx + dy * dy);

        if (distanceToTravel >= distToNext) {
            // Get to next Tile
            posX = targetX;
            posY = targetY;
            pathIndex++;
            distanceToTravel -= distToNext;

            // Events depending on Tile
            if (CoreStorage* c = dynamic_cast<CoreStorage*>(next)) {
                if (coresCarried < coresCapacity) {
                    stealCores(c->takeCores(coresCapacity - coresCarried)); // Taking as many cores as possible
                    distanceToTravel = 0.0f; // Path will change
                }
            }
            else if (ExitZone* ex = dynamic_cast<ExitZone*>(next)) {
                // if (coresCarried > 0) {
                //     // TODO: Tell Game about lost cores
                //     coresCarried = 0;
                // }
            }
        } else {
            // Partially move thowards next Tile
            posX += (dx / distToNext) * distanceToTravel;
            posY += (dy / distToNext) * distanceToTravel;
            distanceToTravel = 0.0f;
        }
    }
}

void Creature::takeDamage(float dmg) {
    if (!alive) return;

    float remaining = dmg;

    // Shield absorbs first
    if (shield > 0) {
        float absorbed = std::min(shield, remaining);
        shield -= absorbed;
        remaining -= absorbed;
        return;
    }

    // Then health
    if (remaining > 0) {
        health -= remaining;
        if (health <= 0) {
            alive = false;
        }
    }
}

void Creature::stealCores(int amount) {
    coresCarried += amount;
}

int Creature::dropCores() {
    int dropped = coresCarried;
    coresCarried = 0;
    return dropped;
}
