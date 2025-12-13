#include <cmath>
#include "core/towers/gatling.hpp"
#include "core/events.hpp"

#define PIf 3.141592f

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
            events.vfxs.emplace(VFXType::GatlingTracer, m_level, m_x, m_y, m_target->px(), m_target->py());
            events.vfxs.emplace(VFXType::HitSpark, m_level, m_target->px(), m_target->py());
            events.sfxs.push(SFXType::GatlingShoot);
        }
    }

    void Gatling::upgrade() {

    }

    std::string Gatling::spriteId() const noexcept {
        if (!m_target)
            return "tower_gatling_s";

        const float dx = m_target->px() - static_cast<float>(m_x);
        const float dy = m_target->py() - static_cast<float>(m_y);
        const float angle = std::fmod(std::atan2(dy, dx) + 2.0f * PIf, 2.0f * PIf);

        if (angle < 0.393f) return "tower_gatling_e";
        else if (angle < 1.169f) return "tower_gatling_se";
        else if (angle < 1.955f) return "tower_gatling_s";
        else if (angle < 2.740f) return "tower_gatling_sw";
        else if (angle < 3.526f) return "tower_gatling_w";
        else if (angle < 4.311f) return "tower_gatling_nw";
        else if (angle < 5.097f) return "tower_gatling_n";
        else if (angle < 5.882f) return "tower_gatling_ne";
        else return "tower_gatling_e";
    }
    
} // namespace tdg::core
