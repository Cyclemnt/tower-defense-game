#include "../../include/towers/gatling.hpp"   


Gatling::Gatling(int x_, int y_)
                 : Tower(x_, y_, 0 /*au*/, 0 /*ag*/, 50 /*cu*/, 4 /*dmg*/, 3.0f /*rng*/, 4.0f /*rate*/, false /*area*/) {}

Gatling::~Gatling() {}

std::string Gatling::getTypeName() const { return "Gatling"; }
