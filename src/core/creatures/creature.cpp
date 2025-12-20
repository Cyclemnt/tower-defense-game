#include <cmath>
#include "core/creatures/creature.hpp"
#include "core/events.hpp"
#include "core/tile.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

#define PIf 3.141592f

namespace tdg::core {

    Creature::Creature(const Creature::Stats& stats)
        : m_stats(stats), m_health(stats.maxHealth), m_shield(stats.maxShield) {}

    void Creature::update(float dt, Events& events) {
        ++m_tick;
        if (!m_alive || m_path.empty() || m_pathIndex + 1 >= m_path.size()) return;

        float distanceToTravel = m_stats.speed * dt;

        while (distanceToTravel > 0.0f && m_pathIndex + 1 < m_path.size()) {
            const Tile* next = m_path[m_pathIndex + 1];

            float dx = next->x - m_px;
            float dy = next->y - m_py;
            
            float distanceToNextTile = std::sqrt(dx * dx + dy * dy);

            if (distanceToTravel >= distanceToNextTile) {
                // Get to next Tile
                m_px = next->x;
                m_py = next->y;
                m_pathIndex++;
                distanceToTravel -= distanceToNextTile;

                if (next == m_path.back()) {
                    switch (next->type) {
                    case Tile::Type::CoreStorage: events.onPath.emplace(Events::OnPath::Type::ArrivedAtCore, this); break;
                    case Tile::Type::Exit:        events.onPath.emplace(Events::OnPath::Type::ReachedExit, this); break;
                    case Tile::Type::Entry:       events.onPath.emplace(Events::OnPath::Type::ReachedExit, this); break;
                    default: break;
                    }
                }

            } else {
                // Partially move thowards next Tile
                m_px += (dx / distanceToNextTile) * distanceToTravel;
                m_py += (dy / distanceToNextTile) * distanceToTravel;
                distanceToTravel = 0.0f;
            }
        }
    }

    void Creature::takeDamage(float amount) {
        if (!m_alive) return;

        float remaining = amount;

        if (m_shield > 0.0f) {
            float absorbed = std::min(m_shield, remaining);
            m_shield -= absorbed;
            remaining -= absorbed;
            return; // Shield prevents taking damage to life once
        }

        if (remaining > 0.0f) {
            m_health -= remaining;
            if (m_health <= 0.0f) m_alive = false;
        }
    }

    unsigned int Creature::remainingCapacity() const noexcept {
        return m_stats.coresCapacity - m_coresCarried;
    }

    void Creature::stealCores(unsigned int amount) noexcept {
        m_coresCarried = std::min(m_coresCarried + amount, m_stats.coresCapacity);
    }

    unsigned int Creature::dropCores() noexcept {
        unsigned int dropped = m_coresCarried;
        m_coresCarried = 0;
        return dropped;
    }

    void Creature::setPath(const std::vector<const Tile*>& p) noexcept {
        m_path = p;
        m_pathIndex = 0;
    }

    void Creature::setPosition(int x, int y) noexcept {
        m_px = x;
        m_py = y;
    }

    void Creature::leave() noexcept {
        m_stats.bounty = {0u,0u,0u};
        m_alive = false;
    }

    void Creature::draw(IVideoRenderer& vidRenderer) const {
        vidRenderer.drawSprite(spriteId(), m_px, m_py);

        // Cores carried
        float orbitRadius = 0.15f;
        float angleStep = 2.0f * PIf / std::max(m_coresCarried, 1u);
        float time = m_tick * 0.03f; // Rotation speed
        float coreRadius = 0.03f;
        for (int i = 0; i < m_coresCarried; ++i) {
            float angle = time + i * angleStep;
            float x = m_px + std::cos(angle) * orbitRadius + 0.5f;
            float y = m_py + std::sin(angle) * orbitRadius + 0.5f;
            vidRenderer.drawCircle(x, y, coreRadius, {100u,200u,255u,220u}, 0.01f, {150u,220u,255u,100u});
        }

        // Health/Shield bars
        float hpRatio = m_health / m_stats.maxHealth;
        float shieldRatio = m_stats.maxShield > 0.0f ? m_shield / m_stats.maxShield : 0.0f;
        const float barWidth = 0.5f;
        const float barHeight = 0.05f;
        const float x = m_px + (1.0f - barWidth) * 0.5f;
        const float baseY = m_py - barHeight - 0.0625f;
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