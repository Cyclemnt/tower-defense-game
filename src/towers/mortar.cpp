#include "../../include/towers/mortar.hpp"   


Mortar::Mortar(int x_, int y_)
                 : Tower(x_, y_, 0, 0, 75, 48, 4.0f, 0.333333f, true) {}

Mortar::~Mortar() {}

std::string Mortar::getTypeName() const { return "Mortar"; }
