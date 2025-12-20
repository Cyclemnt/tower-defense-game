#ifndef VFX_HPP
#define VFX_HPP

#include <memory>
#include "utility/color.hpp"
#include "core/renderable.hpp"

namespace tdg::core { class IVideoRenderer; }

namespace tdg::core {
    
    class VFX : public Renderable {
    public:
        VFX(unsigned int level, float x1, float y1);
        virtual ~VFX() = default;

        virtual void update(float dt); // Updates time to live of the effect
        bool isAlive() { return m_alive; }

        virtual float zOrder() const noexcept override { return m_y1; } // Used to sort before rendering (higher : in front of)
        int drawLayer() const noexcept override { return 2; } // Used for priority between two equal zOrder (higher : in front of)
        virtual void draw(IVideoRenderer& vidRenderer) const override = 0; // Draws the effect

    protected:
        bool m_alive{true};
        float m_timetolive{1.0f};
        unsigned int m_level{1u};
        float m_x1{0.0f}, m_y1{0.0f};
        int m_z{0};
        utils::Color m_color;
    };

    using VFXPtr = std::unique_ptr<VFX>;

} // namespace tdg::core

#endif // VFX_HPP