#ifndef ROAMING_CORE_HPP
#define ROAMING_CORE_HPP

#include <memory>
#include <vector>
#include <string>
#include "core/renderable.hpp"

namespace tdg::core { class Events; struct Tile; class IVideoRenderer; }

namespace tdg::core {

    class RoamingCore : public Renderable {
    public:
        RoamingCore(unsigned int groupQuantity, float x, float y, std::vector<const Tile*> path);

        virtual void update(float dt, Events& events); // Main function to follow m_path and generate events

        bool isRoaming() const noexcept { return m_roaming; }
        unsigned int groupQuantity() const noexcept { return m_groupQuantity; }

        unsigned int pickUp(unsigned int amount) noexcept;

        float px() const noexcept { return m_px; }
        float py() const noexcept { return m_py; }

        float zOrder() const noexcept override { return m_py; } // Used to sort before rendering (higher : in front of)
        int drawLayer() const noexcept override { return 3; } // Used for priority between two equal zOrder (higher : in front of)
        void draw(IVideoRenderer& vidRenderer) const override; // Draws the creature

    protected:
        float m_px{0.0f}, m_py{0.0f};
        unsigned int m_groupQuantity{0u};
        float m_speed{0.5f};

        size_t m_pathIndex{0};
        std::vector<const Tile*> m_path;

        bool m_roaming{true};
        unsigned long m_tick{0u}; // Number of updates the object lived (for tick driven animation)
    };

} // namespace tdg::core

#endif // ROAMING_CORE_HPP