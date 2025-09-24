#include "../../include/creatures/minion.hpp"   


Minion::Minion()
    : Creature(25, 0, 1, 0, 1, 0) {}

Minion::~Minion() {}

std::string Minion::getTypeName() const { return "Minion"; }
