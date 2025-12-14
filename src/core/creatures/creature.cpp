#include <cmath>
#include "core/creatures/creature.hpp"
#include "core/events.hpp"
#include "core/map.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

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
                    case Tile::Type::CoreStorage: events.pathEvents.push({PathEvent::Type::ArrivedToCore, this}); break;
                    case Tile::Type::Exit:        events.pathEvents.push({PathEvent::Type::ArrivedToExit, this}); break;
                    case Tile::Type::Entry:       events.pathEvents.push({PathEvent::Type::ArrivedToExit, this}); break;
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
        // TODO: carried cores + shield/health bars
    }

} // namespace tdg::core