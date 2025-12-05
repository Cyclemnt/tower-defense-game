#ifndef TOWER_HPP
#define TOWER_HPP

#include <chrono>
#include <string>
#include <memory>
#include <array>
#include <vector>
#include "core/player.hpp"
#include "core/creatures/creature.hpp"
#include "core/events.hpp"

namespace tdg::core {

    class Tower {
    public:
        enum class Type { Gatling, Mortar, Laser };

        struct Stats {
            float damage{0.0f};
            float fireRate{0};
            float range{0};
            Materials cost{0u,0u,0u};
        };

        Tower(const Tower::Stats& stats, int x, int y);
        virtual ~Tower() = default;

        virtual void update(float dt, Events& events, const std::vector<CreaturePtr>& creatures) = 0;

        virtual Creature* acquireTarget(const std::vector<CreaturePtr>& creatures);
        void clearTarget() noexcept { m_target = nullptr; }
        virtual void attack() const;

        const Tower::Stats& stats() const noexcept { return m_stats; }
        int x() const noexcept { return m_x; }
        int y() const noexcept { return m_y; }
        Creature* target() const noexcept { return m_target; }

        virtual Materials cost() const noexcept { return m_stats.cost; }
        virtual Materials sellValue() const noexcept { return m_stats.cost / 2; }

    protected:
        Tower::Stats m_stats;
        int m_x{0}, m_y{0};
        Creature* m_target{nullptr};
        float m_cooldown{0};
    };

    using TowerPtr = std::unique_ptr<Tower>;
    
} // namespace tdg::core

#endif // TOWER_HPP
