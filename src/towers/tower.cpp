#include "../../include/towers/tower.hpp"

Tower::Tower()
    : priceAu(0), priceAg(0), priceCu(0), damage(0), speed(0), range(0), areaDamage(false), level(0) {}

Tower::~Tower() {}

void Tower::attack() const {
}

void Tower::upgrade() {
}
