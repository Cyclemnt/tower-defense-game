#include <cmath>
#include "../../include/towers/gatling.hpp"
#include "../../include/creatures/creature.hpp"
#include "../../include/visual-effects/visualEffect.hpp"

Gatling::Gatling(sf::Vector2i position_) noexcept
    : Tower(position_,
        /* cost */ {
            0u,     // Au
            0u,     // Ag
            50u     // Cu
        },
        /*dmg*/ 4,
        /*rng*/ 3.0f,
        /*rate*/ 4.0f
    ) {}

std::string Gatling::getTextureName(int) const {
    if (!target)
        return "tower_gatling_s.png";

    const sf::Vector2f d = target->getPosition() - static_cast<sf::Vector2f>(position);
    const float angle = std::fmod(std::atan2(d.y, d.x) + 2.0f * M_PIf, 2.0f * M_PIf);

    if (angle < 0.3927f) return "tower_gatling_e.png";
    if (angle < 1.169f)  return "tower_gatling_se.png";
    if (angle < 1.955f)  return "tower_gatling_s.png";
    if (angle < 2.740f)  return "tower_gatling_sw.png";
    if (angle < 3.526f)  return "tower_gatling_w.png";
    if (angle < 4.311f)  return "tower_gatling_nw.png";
    if (angle < 5.097f)  return "tower_gatling_n.png";
    if (angle < 5.882f)  return "tower_gatling_ne.png";
    return "tower_gatling_e.png";
}
