#ifndef TOWER_HPP
#define TOWER_HPP

#include <chrono>
#include <string>
#include <memory>
#include <array>
#include <vector>
#include "player.hpp"
#include "core/creatures/creature.hpp"

namespace tdg::core {

    struct TowerStats {
        float damage{0.0f};
        float fireRate{0};
        float range{0};
        Materials cost{0u,0u,0u};
    };

    class Tower {
    public:
        Tower(const TowerStats& stats, int x, int y);
        virtual ~Tower() = default;

        virtual void update(float dt, const std::vector<CreaturePtr>& creatures) = 0;

        virtual Creature* acquireTarget(const std::vector<CreaturePtr>& creatures);
        void clearTarget() noexcept { m_target = nullptr; }
        virtual void attack() const;

        const TowerStats& stats() const noexcept { return m_stats; }
        int x() const noexcept { return m_x; }
        int y() const noexcept { return m_y; }

        virtual Materials sellValue() const noexcept { return m_stats.cost / 2; }

    protected:
        TowerStats m_stats;
        int m_x{0}, m_y{0};
        Creature* m_target{nullptr};
        float m_cooldown{0};
    };

    using TowerPtr = std::unique_ptr<Tower>;

} // namespace tdg::core

#endif // TOWER_HPP