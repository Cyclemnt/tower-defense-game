#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <memory>
#include <vector>
#include <string>
#include "core/player.hpp"

namespace tdg::core { class Events; struct Tile; class IVideoRenderer; }

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
        virtual std::string spriteId() const noexcept = 0;

        unsigned int remainingCapacity() const noexcept;
        void stealCores(unsigned int amount) noexcept;
        unsigned int dropCores() noexcept;

        void setPath(const std::vector<const Tile*>& p) noexcept;
        void setPosition(int x, int y) noexcept;

        const Tile* nextTile() noexcept { return m_path.at(m_pathIndex); }
        const Tile* destinationTile() noexcept { return m_path.back(); }

        void leave() noexcept;

        Materials loot() const noexcept { return m_stats.bounty; }

        void draw(IVideoRenderer& vidRenderer) const;

    protected:
        Creature::Stats m_stats;
        float m_health{0.0f};
        float m_shield{0.0f};
        float m_px{0.0f}, m_py{0.0f};
        size_t m_pathIndex{0};
        std::vector<const Tile*> m_path;
        unsigned int m_coresCarried{0};
        bool m_alive{true};
        unsigned long m_tick{0u};  ///< Number of updates the object lived (for tick driven animation)
    };

    using CreaturePtr = std::unique_ptr<Creature>;

} // namespace tdg::core

#endif // CREATURE_HPP