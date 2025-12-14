#include <cmath>
#include "core/towers/tower.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

namespace tdg::core {

    Tower::Tower(const Tower::Stats& stats, int x, int y)
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

    void Tower::draw(IVideoRenderer& vidRenderer) const {
        vidRenderer.drawSprite(spriteId(), m_x, m_y);
    }

} // namespace tdg::core