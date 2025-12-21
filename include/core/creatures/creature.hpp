#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <memory>
#include <vector>
#include <string>
#include "core/renderable.hpp"
#include "core/materials.hpp"
#include "core/roamingCore.hpp"

namespace tdg::core { class Events; struct Tile; class IVideoRenderer; }

namespace tdg::core {

    class Creature : public Renderable {
    public:
        enum class Type { Minion, Drone, Tank };

        struct Stats {
            float maxHealth{0.0f};
            float maxShield{0.0f};
            float speed{0.0f};
            unsigned int coresCapacity{0u};
            Materials bounty{0u,0u,0u};
            unsigned int level{1u};
        };

        Creature(const Creature::Stats& stats);
        virtual ~Creature() = default;

        virtual void update(float dt, Events& events, std::vector<RoamingCore>& roamingCores); // Main function to follow m_path and generate events

        void pickUpRoamingCores(std::vector<RoamingCore>& roamingCores);

        bool isAlive() const noexcept { return m_alive; }
        float health() const noexcept { return m_health; }
        float shield() const noexcept { return m_shield; }
        void takeDamage(float amount);

        float px() const noexcept { return m_px; }
        float py() const noexcept { return m_py; }
        virtual std::string spriteId() const noexcept = 0; // To get the a sting ID (used to draw)

        unsigned int remainingCapacity() const noexcept; // To get the amount of cores the creatures can collect
        void stealCores(unsigned int amount) noexcept; // To add cores to the creature
        unsigned int dropCores() noexcept; // To lose all carried cores

        void setPath(const std::vector<const Tile*>& p) noexcept; // Sets the creature's m_path
        void setPosition(int x, int y) noexcept; // Sets the position of the creature

        const Tile* nextTile() noexcept { return m_path.at(m_pathIndex); }
        const Tile* destinationTile() noexcept { return m_path.back(); }

        void leave() noexcept; // To leave the map (making bounty 0 and unaliving the creature)

        Materials loot() const noexcept { return m_stats.bounty; }

        float zOrder() const noexcept override { return m_py; } // Used to sort before rendering (higher : in front of)
        int drawLayer() const noexcept override { return 1; } // Used for priority between two equal zOrder (higher : in front of)
        void draw(IVideoRenderer& vidRenderer) const override; // Draws the creature

    protected:
        Creature::Stats m_stats;
        float m_health{0.0f};
        float m_shield{0.0f};
        float m_px{0.0f}, m_py{0.0f};
        unsigned int m_coresCarried{0};

        size_t m_pathIndex{0};
        std::vector<const Tile*> m_path;

        bool m_alive{true};
        unsigned long m_tick{0u}; // Number of updates the object lived (for tick driven animation)
    };

    using CreaturePtr = std::shared_ptr<Creature>;

} // namespace tdg::core

#endif // CREATURE_HPP