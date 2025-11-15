#ifndef TOWER_HPP
#define TOWER_HPP

#include <chrono>
#include <string>
#include <memory>
#include <array>
#include "player.hpp"

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

        // Returns target creature id.
        virtual int acquireTarget() = 0;

        const TowerStats& stats() const noexcept { return m_stats; }
        int x() const noexcept { return m_x; }
        int y() const noexcept { return m_y; }

        virtual Materials sellValue() const noexcept { return m_stats.cost / 2; }

    protected:
        TowerStats m_stats;
        int m_x{0}, m_y{0};
        std::chrono::milliseconds m_timeSinceLastShot{0};
    };

    using TowerPtr = std::unique_ptr<Tower>;

} // namespace tdg::core

#endif // TOWER_HPP