#include <cmath>
#include "../../include/towers/mortar.hpp"
#include "../../include/creatures/creature.hpp"
#include "../../include/visual-effects/visualEffect.hpp"
#include "../../include/visual-effects/explosionEffect.hpp"
#include "../../include/visual-effects/shellEffect.hpp"

Mortar::Mortar(sf::Vector2i position_) noexcept
        : Tower(position_,
        /* cost */ {
            0u,     // Au
            0u,     // Ag
            75u     // Cu
        },
        /*dmg*/ 48,
        /*rng*/ 4.0f,
        /*rate*/ 0.333333f
    ) {}

void Mortar::update(float deltaTime, const std::vector<std::unique_ptr<Creature>>& creatures) {
    if (target || cooldown > 0.0f)
        cooldown -= deltaTime;

    // Validate target
    if (target && (!target->isAlive() || distance(sf::Vector2f(position), target->getPosition()) > range))
        clearTarget();

    // Acquire new target if needed
    if (!target) {
        if (cooldown < 0.0f)
            cooldown = 0.0f;  // Cooldown cannot be negative when target is lost
        target = selectTarget(creatures);
    }

    // Update shells: move them and handle impact
    for (auto it = shells.begin(); it != shells.end(); ) {
        Shell& s = *it; // Get the element
        sf::Vector2f d = s.target - s.position;
        float travelDist = d.length();

        if (travelDist < s.speed * deltaTime) {
            // Impact: apply splash damage to creatures within explosionRadius
            for (const std::unique_ptr<Creature>& c : creatures) {
                float impactDist = distance(s.target, c->getPosition());
                float damageCoefficient = std::exp(-(impactDist * impactDist) / (s.explosionRadius * s.explosionRadius * 0.25f)); // Gaussian distribution
                if (impactDist < s.explosionRadius)
                    c->takeDamage(damage * damageCoefficient);
            }

            visualEffects.push_back(std::make_unique<ExplosionEffect>(s.target)); // Visual explosion at impact point

            it = shells.erase(it); // Erease element and get new iterator
        } else {
            // advance projectile
            s.position += (d / travelDist) * s.speed * deltaTime;
            ++it; // Go to next element
        }
    }

    // Shoot shells while cooldown let it
    while (target && cooldown <= 0.0f) {
        // Create new projectile
        Shell s{static_cast<sf::Vector2f>(position) + sf::Vector2f(0.0f, -0.6f), target->getPosition(), damage};
        shells.push_back(s);
        // Spawn a visual shell (ShellEffect expects start, end, speed)
        visualEffects.push_back(std::make_unique<ShellEffect>(s.position, s.target, s.speed));
        // Advance cooldown
        cooldown += 1.0f / (fireRate); // seconds
    }
}

std::string Mortar::getTextureName(int) const {
    if (!target) return "tower_mortar_nw.png"; // default idle texture

    const float dx = target->getPosition().x - static_cast<float>(position.x);

    if (dx < -0.1f) return "tower_mortar_nw.png";
    else if (dx >  0.1f) return "tower_mortar_ne.png";
    else return "tower_mortar_n.png";
}
