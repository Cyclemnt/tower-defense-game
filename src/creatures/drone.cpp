#include "../../include/creatures/drone.hpp"   

Drone::Drone()
    : Creature(75 /*hp*/, 25 /*shield*/, 0.4f /*speed*/, 2 /*coresCapacity*/, 0 /*au*/, 0 /*ag*/, 10 /*cu*/) {}

Drone::~Drone() {}

std::string Drone::getTypeName() const { return "Drone"; }
