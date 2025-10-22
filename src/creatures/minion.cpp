#include "../../include/creatures/minion.hpp"   

Minion::Minion(bool boost_)
    : Creature(25 + boost_ * 100 /*hp*/, 0 /*shield*/, 1 /*speed*/, 1 /*coresCapacity*/, 0 /*au*/, 1 /*ag*/, 0 /*cu*/), boost(boost_) {}

Minion::~Minion() {}

std::string Minion::getTextureName(int frame) const {
    if (boost) return "creature_minion_b_" + std::to_string(frame) + ".png";
    else return "creature_minion_" + std::to_string(frame) + ".png";
}
