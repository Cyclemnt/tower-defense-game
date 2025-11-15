#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <string>
#include <chrono>
#include <memory>
#include "player.hpp"

namespace tdg::core {

    struct CreatureStats {
        std::string id;
        float maxHealth{0.0f};
        float maxShield{0.0f};
        float speed{0.0f};
        Materials bounty{0u,0u,0u};
    };

    class Creature {
    public:
        Creature(const CreatureStats& stats, float px, float py);
        virtual ~Creature() = default;

        virtual void update(std::chrono::milliseconds dt) = 0;

        bool isAlive() const noexcept { return m_alive; }
        float health() const noexcept { return m_health; }
        float shield() const noexcept { return m_shield; }
        void takeDamage(float dmg);

        float px() const noexcept { return m_px; }
        float py() const noexcept { return m_py; }

    protected:
        CreatureStats m_stats;
        float m_health{0.0f};
        float m_shield{0.0f};
        float m_px{0.0f}, m_py{0.0f};
        bool m_alive{true};
    };

    using CreaturePtr = std::unique_ptr<Creature>;

} // namespace tdg::core

#endif // CREATURE_HPP