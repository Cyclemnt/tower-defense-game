#ifndef VFX_HPP
#define VFX_HPP

#include <memory>

namespace tdg::core { class IVideoRenderer; }

namespace tdg::core {
    
    class VFX {       
    protected:
        struct Color {
            unsigned int r{255u}, g{255u}, b{255u}, a{255u};
            void setColor(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha = 255u);
        };

        bool m_alive{true};
        float m_timetolive{1.0f};
        unsigned int m_level{1u};
        float m_x1{0.0f}, m_y1{0.0f};
        Color m_color;

    public:
        VFX(unsigned int level, float x1, float y1);
        virtual ~VFX() = default;

        virtual void update(float dt);
        bool isAlive() { return m_alive; }

        virtual void draw(IVideoRenderer& vidRenderer) const = 0;
    };

    using VFXPtr = std::unique_ptr<VFX>;

} // namespace tdg::core

#endif // VFX_HPP