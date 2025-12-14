#ifndef TOWER_HPP
#define TOWER_HPP

#include <memory>
#include <vector>
#include <string>
#include "core/creatures/creature.hpp"

namespace tdg::core { class Events; class IVideoRenderer; }

namespace tdg::core {

    class Tower {
    public:
        enum class Type { Gatling, Mortar, Laser };

        struct Stats {
            float damage{0.0f};
            float fireRate{0};
            float range{0};
            Materials cost{0u,0u,0u};
            Materials upgradeCost{0u,0u,0u};
        };

        Tower(const Tower::Stats& stats, int x, int y);
        virtual ~Tower() = default;

        virtual void update(float dt, Events& events, const std::vector<CreaturePtr>& creatures) = 0;

        virtual Creature* acquireTarget(const std::vector<CreaturePtr>& creatures);
        Creature* target() const noexcept { return m_target; }
        void clearTarget() noexcept { m_target = nullptr; }
        virtual void attack() const;

        virtual void upgrade() = 0;
        unsigned int level() const noexcept { return m_level; }

        int x() const noexcept { return m_x; }
        int y() const noexcept { return m_y; }
        const Tower::Stats& stats() const noexcept { return m_stats; }
        virtual std::string spriteId() const noexcept = 0;

        virtual Materials cost() const noexcept { return m_stats.cost; }
        virtual Materials upgradeCost() const noexcept { return m_stats.upgradeCost; }
        virtual Materials sellValue() const noexcept { return m_stats.cost / 2; }

        virtual void draw(IVideoRenderer& vidRenderer) const;

    protected:
        Tower::Stats m_stats;
        unsigned int m_level{1u};
        int m_x{0}, m_y{0};
        Creature* m_target{nullptr};
        float m_cooldown{0};
    };

    using TowerPtr = std::unique_ptr<Tower>;
    
} // namespace tdg::core

#endif // TOWER_HPP
