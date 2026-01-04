#include <cmath>
#include "core/creatures/mother.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

#define PIf 3.141592f

namespace tdg::core {

    Mother::Mother(unsigned int level) noexcept
        : Creature({
            /* health */ 20000.0f,
            /* shield */ 10000.0f,
            /* speed */ 0.0f,
            /* coresCapacity */ 0u,
            /* loot */ {
                999u,                   // Au
                999u,                   // Ag
                999u,                   // Cu
            },
            level
        }) {}

    std::string Mother::spriteId() const noexcept {
        unsigned int frame = m_tick / 32 % 4;
        unsigned int healthRatio = 4u - static_cast<unsigned int>(m_health / m_stats.maxHealth * 3.0f);
        return "creatures/mother_" + std::to_string(healthRatio) + "_" + std::to_string(frame);
    }

    void Mother::draw(IVideoRenderer& vidRenderer) const {
        vidRenderer.drawSprite(spriteId(), m_px - 3.25f, m_py - 3.25f, 7.5f);

        // Cores carried
        float orbitRadius = 0.15f;
        float angleStep = 2.0f * PIf / std::max(m_coresCarried, 1u);
        float time = m_tick * 0.03f; // Rotation speed
        float coreRadius = 0.03f;
        for (int i = 0; i < m_coresCarried; ++i) {
            float angle = time + i * angleStep;
            float x = m_px + std::cos(angle) * orbitRadius + 0.5f;
            float y = m_py + std::sin(angle) * orbitRadius + 0.5f;
            vidRenderer.drawCircle(x, y, coreRadius, {100u,200u,255u,220u}, 0.03f, {170u,240u,255u,100u});
        }

        // Health/Shield bars
        float hpRatio = m_health / m_stats.maxHealth;
        float shieldRatio = m_stats.maxShield > 0.0f ? m_shield / m_stats.maxShield : 0.0f;
        const float barWidth = 0.5f * 7.5f;
        const float barHeight = 0.05f * 7.5f;
        const float x = m_px + (1.0f - barWidth) * 0.5f;
        const float baseY = m_py - barHeight - 0.0625f - 3.25f;
        // Shield bar
        if (m_stats.maxShield > 0.0f) {
            float y = baseY - (barHeight + 0.03125f);
            vidRenderer.drawRectangle(x, y, barWidth, barHeight, {40u,40u,40u});
            vidRenderer.drawRectangle(x, y, barWidth * shieldRatio, barHeight, {100u,150u,255u,200u});
        }
        // Health bar
        {
            float y = baseY;
            vidRenderer.drawRectangle(x, y, barWidth, barHeight, {40u,40u,40u});
            unsigned int r = static_cast<unsigned int>(255u*(1-hpRatio));
            unsigned int g = static_cast<unsigned int>(255u*hpRatio);
            vidRenderer.drawRectangle(x, y, barWidth * hpRatio, barHeight, {r,g,0u});
        }
    }
    
} // namespace tdg::core
