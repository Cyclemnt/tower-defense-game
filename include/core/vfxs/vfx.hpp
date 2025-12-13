#ifndef VFX_HPP
#define VFX_HPP

#include <optional>
#include <memory>

namespace tdg::core {
    
    class VFX {
    protected:
        bool m_alive{true};
        float m_timetolive{1.0f};
        unsigned int m_level{1u};
        float m_x1{0.0f}, m_y1{0.0f};
        std::optional<float> m_x2, m_y2;
        unsigned int m_red{255u}, m_green{255u}, m_blue{255u}, m_alpha{255u};

        void setColor(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha = 255u);

    public:
        VFX(unsigned int level, float x1, float y1, std::optional<float> x2 = std::nullopt, std::optional<float> y2 = std::nullopt);
        virtual ~VFX() = default;

        virtual void update(float dt);
        bool isAlive() { return m_alive; }
    };

    using VFXPtr = std::unique_ptr<VFX>;

} // namespace tdg::core

#endif // VFX_HPP