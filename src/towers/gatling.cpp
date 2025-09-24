#include "../../include/towers/gatling.hpp"   


Gatling::Gatling(int x_, int y_)
                 : Tower(x_, y_, 0, 0, 50, 4, 3.0f, 4.0f, false) {}

Gatling::~Gatling() {}

std::string Gatling::getTypeName() const { return "Gatling"; }
