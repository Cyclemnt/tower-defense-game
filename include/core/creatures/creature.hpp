#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <string>
#include <chrono>
#include <memory>
#include <vector>
#include "core/map.hpp"
#include "core/player.hpp"
#include "core/interfaces/iPathfinder.hpp"
namespace tdg::core { class Events; } // Forward declaration

namespace tdg::core {

    class Creature {
    public:
        enum class Type { Minion, MinionB, Drone, DroneB, Tank, TankB };

        struct Stats {
            float maxHealth{0.0f};
            float maxShield{0.0f};
            float speed{0.0f};
            unsigned int coresCapacity{0u};
            Materials bounty{0u,0u,0u};
            bool boosted{false};
        };

        Creature(const Creature::Stats& stats);
        virtual ~Creature() = default;

        virtual void update(float dt, Events& events);

        bool isAlive() const noexcept { return m_alive; }
        float health() const noexcept { return m_health; }
        float shield() const noexcept { return m_shield; }
        void takeDamage(float amount);

        float px() const noexcept { return m_px; }
        float py() const noexcept { return m_py; }

        void stealCores(unsigned int amount) noexcept;
        unsigned int dropCores() noexcept;

        void setPath(const std::vector<const Tile*>& p) noexcept;
        void setPosition(int x, int y) noexcept;

        const Tile* nextTile() noexcept { return *m_path.begin(); }
        const Tile* destinationTile() noexcept { return *m_path.end(); }

        void leave() noexcept;

        Materials loot() const noexcept { return m_stats.bounty; }

    protected:
        Creature::Stats m_stats;
        float m_health{0.0f};
        float m_shield{0.0f};
        float m_px{0.0f}, m_py{0.0f};
        size_t m_pathIndex{0};
        std::vector<const Tile*> m_path;
        unsigned int m_coresCarried{0};
        bool m_alive{true};
    };

    using CreaturePtr = std::unique_ptr<Creature>;

} // namespace tdg::core

#endif // CREATURE_HPP