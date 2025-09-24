#include "../../include/towers/laser.hpp"   


Laser::Laser(int x_, int y_)
                 : Tower(x_, y_, 0, 10, 100, 3, 3.0f, 15.0f, false) {}

Laser::~Laser() {}

std::string Laser::getTypeName() const { return "Laser"; }
