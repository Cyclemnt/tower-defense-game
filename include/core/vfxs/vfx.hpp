#ifndef VFX_HPP
#define VFX_HPP

#include <memory>
#include "utility/color.hpp"

namespace tdg::core { class IVideoRenderer; }

namespace tdg::core {
    
    class VFX {
    public:
        VFX(unsigned int level, float x1, float y1);
        virtual ~VFX() = default;

        virtual void update(float dt); // Updates time to live of the effect
        bool isAlive() { return m_alive; }

        virtual void draw(IVideoRenderer& vidRenderer) const = 0; // Draws the effect

    protected:
        bool m_alive{true};
        float m_timetolive{1.0f};
        unsigned int m_level{1u};
        float m_x1{0.0f}, m_y1{0.0f};
        utils::Color m_color;
    };

    using VFXPtr = std::unique_ptr<VFX>;

} // namespace tdg::core

#endif // VFX_HPP