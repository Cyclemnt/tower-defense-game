#ifndef TOWER_HPP
#define TOWER_HPP

#include <chrono>
#include <string>
#include <memory>
#include <array>
#include <vector>
#include "player.hpp"
#include "creature.hpp"

namespace tdg::core {

    struct TowerStats {
        std::string id;
        float range{0};
        float damage{0.0f};
        std::chrono::milliseconds fireRate{0};
        Materials cost{0u,0u,0u};
    };

    class Tower {
    public:
        Tower(const TowerStats& stats, int x, int y);
        virtual ~Tower() = default;

        virtual void update(std::chrono::milliseconds dt) = 0;

        virtual Creature* acquireTarget(const std::vector<std::unique_ptr<Creature>>& creatures);
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
        std::chrono::milliseconds m_timeSinceLastShot{0};
    };

    using TowerPtr = std::unique_ptr<Tower>;

} // namespace tdg::core

#endif // TOWER_HPP