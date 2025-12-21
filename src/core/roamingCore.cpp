#include <cmath>
#include "core/roamingCore.hpp"
#include "core/tile.hpp"
#include "core/events.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

#define PIf 3.141592

namespace tdg::core {

    RoamingCore::RoamingCore(unsigned int groupQuantity, float x, float y, std::vector<const Tile*> path)
        : m_groupQuantity(groupQuantity), m_px(x), m_py(y), m_path(path) {}

    void RoamingCore::update(float dt, Events& events) {
        ++m_tick;
        if (m_path.empty() || m_pathIndex + 1 >= m_path.size()) return;

        float distanceToTravel = m_speed * dt;

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
                    m_roaming = false; 
                }

            } else {
                // Partially move thowards next Tile
                m_px += (dx / distanceToNextTile) * distanceToTravel;
                m_py += (dy / distanceToNextTile) * distanceToTravel;
                distanceToTravel = 0.0f;
            }
        }
    }

    unsigned int RoamingCore::pickUp(unsigned int amount) noexcept {
        amount = amount < m_groupQuantity ? amount : m_groupQuantity;
        m_groupQuantity -= amount;
        return amount;
    }

    void RoamingCore::draw(IVideoRenderer& vidRenderer) const {
        // Cores carried
        float orbitRadius = 0.15f;
        float angleStep = 2.0f * PIf / std::max(m_groupQuantity, 1u);
        float time = m_tick * 0.03f; // Rotation speed
        float coreRadius = 0.04f;
        for (int i = 0; i < m_groupQuantity; ++i) {
            float angle = time + i * angleStep;
            float x = m_px - std::cos(angle) * orbitRadius + 0.5f;
            float y = m_py + std::sin(angle) * orbitRadius + 0.5f;
            vidRenderer.drawCircle(x, y, coreRadius, {100u,200u,255u,220u}, 0.04f, {170u,240u,255u,100u});
        }
    }
    
} // namespace tdg::core
