#include "../../include/towers/gatling.hpp"
#include "../../include/visual-effects/visualEffect.hpp"
#include "../../include/creatures/creature.hpp"

Gatling::Gatling(int x_, int y_)
    : Tower(x_, y_, 0 /*au*/, 0 /*ag*/, 50 /*cu*/, 4 /*dmg*/, 3.0f /*rng*/, 4.0f /*rate*/) {}

Gatling::~Gatling() {}

std::string Gatling::getTextureName(int frame) const {
    if (!target) return "tower_gatling_nw.png";

    float dx = target->getPosition()[0] - x;
    float dy = target->getPosition()[1] - y;

    std::string texture = "tower_gatling_";
    
    if (dx < 0) texture += (dy < 0) ? "nw.png" : (dy > 0) ? "sw.png" : "w.png";  // left
    else if (dx > 0) texture += (dy < 0) ? "ne.png" : (dy > 0) ? "se.png" : "e.png";  // right
    else texture += (dy < 0) ? "n.png" : (dy > 0) ? "s.png" : "nw.png";  // same x (NW by default)

    return texture;
}
