#include "core/towers/tower.hpp"
#include <cmath>

namespace tdg::core {

    Tower::Tower(const TowerStats& stats, int x, int y)
        : m_stats(stats), m_x(x), m_y(y) {}

    Creature* Tower::acquireTarget(const std::vector<CreaturePtr>& creatures) {
        Creature* best = nullptr;
        float closest = std::numeric_limits<float>::max();

        for (auto& c : creatures) {
            if (!c->isAlive()) continue;
            float dx = c->px() - m_x;
            float dy = c->py() - m_y;
            float dist = std::sqrt(dx * dx + dy * dy);
            if (dist <= m_stats.range && dist < closest) {
                closest = dist;
                best = c.get();
            }
        }

        return best;
    }

    void Tower::attack() const {
        if (!m_target) return;
        m_target->takeDamage(m_stats.damage);
    }

} // namespace tdg::core