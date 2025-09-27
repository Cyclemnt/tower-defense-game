#include "../../include/towers/mortar.hpp"   


Mortar::Mortar(int x_, int y_)
                 : Tower(x_, y_, 0 /*au*/, 0 /*ag*/, 75 /*cu*/, 48 /*dmg*/, 4.0f /*rng*/, 0.333333f /*rate*/, true /*area*/) {}

Mortar::~Mortar() {}

std::string Mortar::getTypeName() const { return "Mortar"; }
