#include <cmath>
#include "core/towers/laser.hpp"
#include "core/events.hpp"

namespace tdg::core {

    Laser::Laser(int x, int y) noexcept
        : Tower({
            /*dmg*/ 0.1f,
            /*rate*/ 15.0f,
            /*rng*/ 3.0f,
            /* cost */ {
                0u,     // Au
                10u,    // Ag
                100u    // Cu
            },
            /* upgrade cost */ 10u // Au
        }, x, y) {}

    void Laser::update(float dt, Events& events, const std::vector<CreaturePtr>& creatures) {
        ++m_tick;
        if (m_target || m_cooldown > 0.0f)
            m_cooldown -= dt;

        // Validate target
        if (m_target) {
            float dx = m_target->px() - m_x;
            float dy = m_target->py() - m_y;
            float creatureDistance = std::sqrt(dx * dx + dy * dy);
            if (!m_target->isAlive() || creatureDistance > m_stats.range) {
                clearTarget();
                // Reset damage scale over time
                m_lockTime = 0.0f; // Reset lock timer
                m_damageScale = 1.0f; // Reset damage coefficient
                m_stats.damage = m_baseDamage; // Reset damage
            }
        }

        // Update damage scale over time
        if (m_target) {
            m_lockTime += dt;
            m_damageScale = 2.9f * std::min(m_lockTime, 10.0f) + 1.0; // Scales from 1x at 0s to 30x at 10s: ((maxScale-minScale)/maxTime * min(time, maxTime) + 1)
            m_stats.damage = m_baseDamage * m_damageScale;
        }

        // Acquire new target if needed
        if (!m_target) {
            m_cooldown = std::max(m_cooldown, 0.0f);
            m_target = acquireTarget(creatures);
            m_lockTime = 0.0f;
        }

        // Attack while cooldown allows
        while (m_target && m_cooldown <= 0.0f) {
            attack();
            m_cooldown += 1.0f / m_stats.fireRate;
            events.vfxs.emplace(VFXType::LaserBeam, m_level, m_x, m_y, m_target->px(), m_target->py());
            events.sfxs.push(SFXType::LaserShoot);
        }
    }

    void Laser::upgrade() {
        m_stats.fireRate *= 1.20;
    }

    std::string Laser::spriteId() const noexcept {
        unsigned int frame = m_tick / 8 % 4;
        return "towers/laser_" + std::to_string(m_level) + "_" + std::to_string(frame);
    }
    
} // namespace tdg::core
