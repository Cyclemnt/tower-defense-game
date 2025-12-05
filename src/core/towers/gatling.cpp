#include "core/towers/gatling.hpp"
#include <cmath>

namespace tdg::core {

    Gatling::Gatling(int x, int y) noexcept
        : Tower({
            /*dmg*/ 4,
            /*rate*/ 4.0f,
            /*rng*/ 3.0f,
            /* cost */ {
                0u,     // Au
                0u,     // Ag
                50u     // Cu
            },
            /* upgrade cost */ 10u // Au
        }, x, y) {}

    void Gatling::update(float dt, Events& events, const std::vector<CreaturePtr>& creatures) {
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

        // Attack while cooldown allows
        while (m_target && m_cooldown <= 0.0f) {
            attack();
            m_cooldown += 1.0f / m_stats.fireRate;
            events.vfxs.emplace_back(VFXType::GatlingTracer, m_x, m_y, m_target->px(), m_target->py());
            events.vfxs.emplace_back(VFXType::HitSpark, m_target->px(), m_target->py());
            events.sfxs.push(SFXType::GatlingShoot);
        }
    }

    void Gatling::upgrade() {

    }
    
} // namespace tdg::core
