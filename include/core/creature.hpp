#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <string>
#include <chrono>
#include <memory>
#include <vector>
#include "core/map.hpp"
#include "core/player.hpp"
#include "core/interfaces/iPathfinder.hpp"

namespace tdg::core {

    struct CreatureStats {
        std::string id;
        float maxHealth{0.0f};
        float maxShield{0.0f};
        float speed{0.0f};
        unsigned int coresCapacity{0u};
        Materials bounty{0u,0u,0u};
    };

    class Creature {
    public:
        Creature(const CreatureStats& stats, float px, float py);
        virtual ~Creature() = default;

        virtual void update(float dt);

        bool isAlive() const noexcept { return m_alive; }
        float health() const noexcept { return m_health; }
        float shield() const noexcept { return m_shield; }
        void takeDamage(float amount);

        float px() const noexcept { return m_px; }
        float py() const noexcept { return m_py; }

        void stealCores(unsigned int amount) noexcept;
        unsigned int dropCores() noexcept;

        void setPath(const std::vector<const Tile*>& p) noexcept;

        Materials getLoot() const noexcept { return m_stats.bounty; }

    protected:
        CreatureStats m_stats;
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