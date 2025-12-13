#include <cmath>
#include "core/towers/mortar.hpp"
#include "core/events.hpp"

namespace tdg::core {

    Mortar::Mortar(int x, int y) noexcept
        : Tower({
            /*dmg*/ 48,
            /*rate*/ 0.333333f,
            /*rng*/ 4.0f,
            /* cost */ {
                0u,     // Au
                0u,     // Ag
                75u     // Cu
            },
            /* upgrade cost */ 10u // Au
        }, x, y) {}

    void Mortar::update(float dt, Events& events, const std::vector<CreaturePtr>& creatures) {
        if (m_target || m_cooldown > 0.0f)
            m_cooldown -= dt;

        // Validate target
        float dx = m_target->px() - m_x;
        float dy = m_target->py() - m_y;
        float creatureDistance = std::sqrt(dx * dx + dy * dy);
        if (m_target && (!m_target->isAlive() || creatureDistance > m_stats.range))
            clearTarget();

        // Acquire new target if needed
        if (!m_target) {
            m_cooldown = std::max(m_cooldown, 0.0f);
            m_target = acquireTarget(creatures);
        }

        // Update shells: move them and handle impact
        for (auto it = m_shells.begin(); it != m_shells.end(); ) {
            Shell& s = *it; // Get the element

            float dx = s.endX - s.curX;
            float dy = s.endY - s.curY;
            float travelDist = std::sqrt(dx * dx + dy * dy);

            if (travelDist < m_shellSpeed * dt) {
                // Impact: apply splash damage to creatures within explosionRadius
                for (const CreaturePtr& c : creatures) {
                    float impactdx = c->px() - s.curX;
                    float impactdy = c->py() - s.curY;
                    float impactDist = std::sqrt(impactdx * impactdx + impactdy * impactdy);
                    if (impactDist < m_shellExplosionRadius)
                        c->takeDamage(m_stats.damage);
                }
                events.vfxs.emplace(VFXType::Explosion, m_level, s.endX, s.endY);
                events.sfxs.push(SFXType::MortarHit);
                it = m_shells.erase(it); // Erease element and get new iterator

            } else {
                // advance projectile
                s.curX += (dx / travelDist) * m_shellSpeed * dt;
                s.curY += (dy / travelDist) * m_shellSpeed * dt;
                ++it; // Go to next element
            }
        }

        // Shoot shells while cooldown let it
        while (m_target && m_cooldown <= 0.0f) {
            // Create new projectile
            Shell newShell{static_cast<float>(m_x), static_cast<float>(m_y), m_target->px(), m_target->py()};
            m_shells.push_back(newShell);
            m_cooldown += 1.0f / m_stats.fireRate;
            events.sfxs.push(SFXType::MortarShoot);
        }
    }

    void Mortar::upgrade() {

    }

    std::string Mortar::spriteId() const noexcept {
        if (!m_target) return "tower_mortar_n"; // default idle texture

        const float dx = m_target->px() - static_cast<float>(m_x);

        if (dx < -0.1f) return "tower_mortar_nw";
        else if (dx >  0.1f) return "tower_mortar_ne";
        else return "tower_mortar_n";
    }
    
} // namespace tdg::core
