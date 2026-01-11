#include <cmath>
#include "core/towers/wall.hpp"
#include "core/events.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

#define PIf 3.141592f

namespace tdg::core {

    Wall::Wall(int x, int y, Materials cost) noexcept
        : Tower({
            /*dmg*/ 0.0f,
            /*rate*/ 0.0f,
            /*rng*/ 0.0f,
            /* cost */ cost,
            /* upgrade cost */ 10u // Au
        }, x, y) {}

    void Wall::update(float dt, Events& events, const std::vector<CreaturePtr>& creatures) {
        // CreaturePtr target = m_target.lock();
        // if (target || m_cooldown > 0.0f)
        //     m_cooldown -= dt;

        // // Validate target
        // if (target) {
        //     float dx = target->px() - m_x;
        //     float dy = target->py() - m_y;
        //     float creatureDistance = std::sqrt(dx * dx + dy * dy);
        //     if (!target->isAlive() || creatureDistance > m_stats.range) {
        //         m_target.reset(); target.reset();
        //     }
        // }

        // // Acquire new target if needed
        // if (!target) {
        //     m_cooldown = std::max(m_cooldown, 0.0f);
        //     m_target = acquireTarget(creatures);
        // }

        // // Attack while cooldown allows
        // while (target && m_cooldown <= 0.0f) {
        //     attack();
        //     m_cooldown += 1.0f / m_stats.fireRate;
        //     events.vfxs.emplace(Events::NewVFX::Type::GatlingTracer, m_level, m_x, m_y, target->px(), target->py());
        //     events.vfxs.emplace(Events::NewVFX::Type::HitSpark, m_level, target->px(), target->py());
        //     events.sfxs.emplace(Events::NewSFX::Type::GatlingShoot, m_level);
        // }
    }

    bool Wall::upgrade() {
        // switch (m_level) {
        //     case 1u:
        //         m_level += 1;
        //         m_stats.fireRate = 4.0f;
        //         m_stats.damage = 5.0f;
        //         return true;

        //     case 2u:
        //         m_level += 1;
        //         m_stats.fireRate = 5.0f;
        //         m_stats.damage = 6.0f;
        //         return true;
            
        //     default:
        //         return false;
        // }
        return false;
    }

    std::string Wall::spriteId() const noexcept {
        return "towers/wall";
    }

    void Wall::draw(IVideoRenderer& vidRenderer) const {
        vidRenderer.drawSprite(spriteId(), m_x, m_y); // y offset to account for towers sprite size
    }
    
} // namespace tdg::core
