#include "../../include/creatures/minion.hpp"   


Minion::Minion()
    : Creature(25 /*hp*/, 0 /*shield*/, 1 /*speed*/, 1 /*coresCapacity*/, 0 /*au*/, 1 /*ag*/, 0 /*cu*/) {}

Minion::~Minion() {}

std::string Minion::getTypeName() const { return "Minion"; }
