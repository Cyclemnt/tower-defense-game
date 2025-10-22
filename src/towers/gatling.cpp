#include <cmath>
#include "../../include/towers/gatling.hpp"
#include "../../include/visual-effects/visualEffect.hpp"
#include "../../include/creatures/creature.hpp"

Gatling::Gatling(int x_, int y_)
    : Tower(x_, y_, 0 /*au*/, 0 /*ag*/, 50 /*cu*/, 4 /*dmg*/, 3.0f /*rng*/, 4.0f /*rate*/) {}

Gatling::~Gatling() {}

std::string Gatling::getTextureName(int frame) const {
    std::string texture = "tower_gatling_";

    if (!target) texture += "s.png";
    else {    
        float dx = target->getPosition()[0] - x;
        float dy = target->getPosition()[1] - y;
        float angle = std::fmod(std::atan2(dy, dx) + (2.0f * M_PIf), 2.0f * M_PIf);
        
        if (angle < 0.3926991f) texture += "e.png";
        else if (angle < 1.169371f) texture += "se.png";
        else if (angle < 1.9547688f) texture += "s.png";
        else if (angle < 2.7401669f) texture += "sw.png";
        else if (angle < 3.5255651f) texture += "w.png";
        else if (angle < 4.3109633f) texture += "nw.png";
        else if (angle < 5.0963614f) texture += "n.png";
        else if (angle < 5.8817596f) texture += "ne.png";
        else texture += "e.png";    
    }

    return texture;
}
