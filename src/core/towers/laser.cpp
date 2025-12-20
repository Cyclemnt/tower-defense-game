#include <cmath>
#include "core/towers/laser.hpp"
#include "core/events.hpp"

namespace tdg::core {

    Laser::Laser(int x, int y, Materials cost) noexcept
        : Tower({
            /*dmg*/ 0.1f,
            /*rate*/ 15.0f,
            /*rng*/ 3.0f,
            /* cost */ cost,
            /* upgrade cost */ 10u // Au
        }, x, y) {}

    void Laser::update(float dt, Events& events, const std::vector<CreaturePtr>& creatures) {
        ++m_tick;
        CreaturePtr target = m_target.lock();
        if (target || m_cooldown > 0.0f)
            m_cooldown -= dt;

        // Validate target
        if (target) {
            float dx = target->px() - m_x;
            float dy = target->py() - m_y;
            float creatureDistance = std::sqrt(dx * dx + dy * dy);
            if (!target->isAlive() || creatureDistance > m_stats.range) {
                // Reset damage scale over time
                m_lockTime = 0.0f; // Reset lock timer
                m_damageScale = 1.0f; // Reset damage coefficient
                m_stats.damage = m_baseDamage; // Reset damage
                m_target.reset(); target.reset();
            }
        }

        // Update damage scale over time
        if (target) {
            m_lockTime += dt;
            m_damageScale = 2.9f * std::min(m_lockTime, 10.0f) + 1.0; // Scales from 1x at 0s to 30x at 10s: ((maxScale-minScale)/maxTime * min(time, maxTime) + 1)
            m_stats.damage = m_baseDamage * m_damageScale;
        }

        // Acquire new target if needed
        if (!target) {
            m_cooldown = std::max(m_cooldown, 0.0f);
            m_target = acquireTarget(creatures);
            m_lockTime = 0.0f;
        }

        // Attack while cooldown allows
        while (target && m_cooldown <= 0.0f) {
            attack();
            m_cooldown += 1.0f / m_stats.fireRate;
            events.vfxs.emplace(Events::NewVFX::Type::LaserBeam, m_level, m_x, m_y, target->px(), target->py());
            events.sfxs.emplace(Events::NewSFX::Type::LaserShoot, m_level);
        }
    }

    bool Laser::upgrade() {
        switch (m_level) {
            case 1u:
                m_level += 1;
                m_stats.range = 3.5f;
                m_stats.damage = 0.12f;
                return true;

            case 2u:
                m_level += 1;
                m_stats.range = 4.0f;
                m_stats.damage = 0.14f;
                return true;
            
            default:
                return false;
        }
    }

    std::string Laser::spriteId() const noexcept {
        unsigned int frame = m_tick / 8 % 4;
        return "towers/laser_" + std::to_string(m_level) + "_" + std::to_string(frame);
    }
    
} // namespace tdg::core
