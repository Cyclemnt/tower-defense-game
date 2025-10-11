#include "../../include/visual-effects/visualEffect.hpp"

bool VisualEffect::isAlive() const { return alive; }

void VisualEffect::die() { alive = false; }