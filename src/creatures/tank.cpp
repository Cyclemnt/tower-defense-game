#include "../../include/creatures/tank.hpp"   

Tank::Tank()
    : Creature(125 /*hp*/, 75 /*shield*/, 0.25f /*speed*/, 3 /*coresCapacity*/, 1 /*au*/, 2 /*ag*/, 10 /*cu*/) {}

Tank::~Tank() {}

std::string Tank::getTextureName(int frame) const {
    return "creature_tank_" + std::to_string(frame) + ".png";
}
