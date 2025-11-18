#include "core/creature.hpp"
#include <cmath>

namespace tdg::core {

    Creature::Creature(const CreatureStats& stats, float px, float py)
        : m_stats(stats), m_health(stats.maxHealth), m_shield(stats.maxShield), m_px(px), m_py(py) {}

    void Creature::update(std::chrono::milliseconds dt) {
        if (!m_alive || m_path.empty() || m_pathIndex + 1 >= m_path.size()) return;
        float seconds = std::chrono::duration<float>(dt).count();

        float distanceToTravel = m_stats.speed * seconds;

        while (distanceToTravel > 0.0f && m_pathIndex + 1 < m_path.size()) {
            PathPoint current = m_path[m_pathIndex];
            PathPoint next = m_path[m_pathIndex + 1];

            PathPoint target = next;

            float dx = target.x - m_px;
            float dy = target.y - m_py;
            
            float distanceToNextTile = std::sqrt(dx * dx + dy * dy);

            if (distanceToTravel >= distanceToNextTile) {
                // Get to next Tile
                m_px = target.x;
                m_py = target.y;
                m_pathIndex++;
                distanceToTravel -= distanceToNextTile;

                // Events depending on Tile
                // if (const CoreStorage* c = dynamic_cast<const CoreStorage*>(next)) {
                //     if (coresCarried < coresCapacity) {
                //         if (coresCapacity - coresCarried < 0) throw std::runtime_error("Creature carries more cores than its capacity");
                //         stealCores(c->takeCores(coresCapacity - coresCarried)); // Taking as many cores as possible
                //         distanceToTravel = 0.0f; // Path will change
                //     }
                // }
                // else if (const ExitZone* ex = dynamic_cast<const ExitZone*>(next)) {
                //     // Nothing to do, Game will do its job
                // }
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

    void Creature::stealCores(unsigned int amount) {
        m_coresCarried = std::min(m_coresCarried + amount, m_stats.coresCapacity);
    }

    unsigned int Creature::dropCores() noexcept {
        unsigned int dropped = m_coresCarried;
        m_coresCarried = 0;
        return dropped;
    }

    void Creature::setPath(const std::vector<PathPoint>& p) {
        m_path = p;
        m_pathIndex = 0;
    }

} // namespace tdg::core