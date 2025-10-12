#include "../../include/creatures/minion.hpp"   

Minion::Minion()
    : Creature(25 /*hp*/, 0 /*shield*/, 1 /*speed*/, 1 /*coresCapacity*/, 0 /*au*/, 1 /*ag*/, 0 /*cu*/) {}

Minion::~Minion() {}

std::string Minion::getTextureName(int frame) const {
    return "creature_minion_" + std::to_string(frame) + ".png";
}
