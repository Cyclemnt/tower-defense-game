#include "../../include/creatures/creature.hpp"

Creature::Creature()
    : health(0), shield(0), speed(0), carriedCores(0), path({}) {}

Creature::~Creature() {}

void Creature::move() {
}

void Creature::takeDamage(int amount) {
}

void Creature::stealCore() {
}

void Creature::exitMap() {
}
