#include "../../include/creatures/tank.hpp"   

Tank::Tank(bool boost_)
    : Creature(125 + boost_ * 25 /*hp*/, 75 + boost_ * 225/*shield*/, 0.25f /*speed*/, 3 /*coresCapacity*/, 1 /*au*/, 2 /*ag*/, 10 + boost_ * 30 /*cu*/), boost(boost_) {}

Tank::~Tank() {}

std::string Tank::getTextureName(int frame) const {
    if (boost) return "creature_tank_b_" + std::to_string(frame) + ".png";
    else return "creature_tank_" + std::to_string(frame) + ".png";
}
