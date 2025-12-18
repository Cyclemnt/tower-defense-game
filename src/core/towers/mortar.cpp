#include <cmath>
#include "core/towers/mortar.hpp"
#include "core/events.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

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
        if (m_target) {
            float dx = m_target->px() - m_x;
            float dy = m_target->py() - m_y;
            float creatureDistance = std::sqrt(dx * dx + dy * dy);
            if (!m_target->isAlive() || creatureDistance > m_stats.range)
                clearTarget();
        }

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
                events.vfxs.emplace(Events::VFX::Type::Explosion, m_level, s.endX, s.endY);
                events.sfxs.emplace(Events::SFX::Type::MortarHit, m_level);
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
            Shell newShell{static_cast<float>(m_x), static_cast<float>(m_y) - 0.3f, m_target->px(), m_target->py()};
            m_shells.push_back(newShell);
            m_cooldown += 1.0f / m_stats.fireRate;
            events.sfxs.emplace(Events::SFX::Type::MortarShoot, m_level);
        }
    }

    bool Mortar::upgrade() {
        switch (m_level) {
            case 1u:
                m_level += 1;
                m_stats.range = 3.5f;
                m_stats.fireRate = 0.5f;
                m_stats.damage = 58.0f;
                return true;

            case 2u:
                m_level += 1;
                m_stats.range = 5.0f;
                m_stats.fireRate = 0.2f;
                m_stats.damage = 98.0f;
                return true;
            
            default:
                return false;
        }
    }

    std::string Mortar::spriteId() const noexcept {
        float dx = m_target ? m_target->px() - static_cast<float>(m_x) : 0.0f;
        float cooldownRatio = m_cooldown * m_stats.fireRate;

        switch (m_level) {
            case 1u:
                if (dx < -0.1f) return "towers/mortar_1_nw";
                if (dx > 0.1f) return "towers/mortar_1_ne";
                else return "towers/mortar_1_n";

            case 2u:
                if (cooldownRatio > 0.75f) return "towers/mortar_2_3";
                if (cooldownRatio > 0.50f) return "towers/mortar_2_0";
                if (cooldownRatio > 0.25f) return "towers/mortar_2_1";
                else return "towers/mortar_2_2";

            case 3u:
                if (cooldownRatio > 0.95f) return "towers/mortar_3_2";
                if (cooldownRatio > 0.60f) return "towers/mortar_3_3";
                if (cooldownRatio > 0.25f) return "towers/mortar_3_0";
                else return "towers/mortar_3_2";

            default: return " ";
        }
    }

    void Mortar::draw(IVideoRenderer& vidRenderer) const {
        for (auto& s : m_shells) {
            utils::Color color = {180u,180u,180u};
            vidRenderer.drawCircle(s.curX + 0.5f, s.curY + 0.5f, 0.1f, color);
        }

        vidRenderer.drawSprite(spriteId(), m_x, m_y - 0.7f);
    }
    
} // namespace tdg::core
