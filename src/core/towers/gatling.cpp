#include <cmath>
#include "core/towers/gatling.hpp"
#include "core/events.hpp"

#define PIf 3.141592f

namespace tdg::core {

    Gatling::Gatling(int x, int y) noexcept
        : Tower({
            /*dmg*/ 4,
            /*rate*/ 3.0f,
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

        // Attack while cooldown allows
        while (m_target && m_cooldown <= 0.0f) {
            attack();
            m_cooldown += 1.0f / m_stats.fireRate;
            events.vfxs.emplace(Events::VFX::Type::GatlingTracer, m_level, m_x, m_y, m_target->px(), m_target->py());
            events.vfxs.emplace(Events::VFX::Type::HitSpark, m_level, m_target->px(), m_target->py());
            events.sfxs.emplace(Events::SFX::Type::GatlingShoot, m_level);
        }
    }

    bool Gatling::upgrade() {
        switch (m_level) {
            case 1u:
                m_level += 1;
                m_stats.fireRate = 4.0f;
                m_stats.damage = 5.0f;
                return true;

            case 2u:
                m_level += 1;
                m_stats.fireRate = 5.0f;
                m_stats.damage = 6.0f;
                return true;
            
            default:
                return false;
        }
    }

    std::string Gatling::spriteId() const noexcept {
        if (!m_target)
            return "towers/gatling_" + std::to_string(m_level) + "_s";

        const float dx = m_target->px() - static_cast<float>(m_x);
        const float dy = m_target->py() - static_cast<float>(m_y);
        const float angle = std::fmod(std::atan2(dy, dx) + 2.0f * PIf, 2.0f * PIf);

        if (angle < 0.393f) return "towers/gatling_" + std::to_string(m_level) + "_e";
        else if (angle < 1.169f) return "towers/gatling_" + std::to_string(m_level) + "_se";
        else if (angle < 1.955f) return "towers/gatling_" + std::to_string(m_level) + "_s";
        else if (angle < 2.740f) return "towers/gatling_" + std::to_string(m_level) + "_sw";
        else if (angle < 3.526f) return "towers/gatling_" + std::to_string(m_level) + "_w";
        else if (angle < 4.311f) return "towers/gatling_" + std::to_string(m_level) + "_nw";
        else if (angle < 5.097f) return "towers/gatling_" + std::to_string(m_level) + "_n";
        else if (angle < 5.882f) return "towers/gatling_" + std::to_string(m_level) + "_ne";
        else return "towers/gatling_" + std::to_string(m_level) + "_e";
    }
    
} // namespace tdg::core
