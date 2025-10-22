#include "../../include/creatures/drone.hpp"   

Drone::Drone(bool boost_)
    : Creature(75 + boost_ * 50 /*hp*/, 25 + boost_ * 75 /*shield*/, 0.4f + boost_ * 0.3f /*speed*/, 2 /*coresCapacity*/, 0 /*au*/, 0 + boost_ * 5 /*ag*/, 10 + boost_ * 30 /*cu*/), boost(boost_) {}

Drone::~Drone() {}

std::string Drone::getTextureName(int frame) const {
    if (boost) return "creature_drone_b_" + std::to_string(frame) + ".png";
    else return "creature_drone_" + std::to_string(frame) + ".png";
}
