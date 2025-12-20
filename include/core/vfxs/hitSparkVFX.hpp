#ifndef HIT_SPARK_VFX_HPP
#define HIT_SPARK_VFX_HPP

#include <vector>
#include "core/vfxs/vfx.hpp"

namespace tdg::core {

    class HitSparkVFX final : public VFX {
    public:
        HitSparkVFX(unsigned int level, float x1, float y1);

        void update(float dt) override; // Updates time to live of the effect and particles position

        void draw(IVideoRenderer& vidRenderer) const override; // Draws the effect
        
    private:
        struct Particle {
            float dirX{0.0f}, dirY{0.0f};
            float speed{0.0f};
            float radius{0.0f};
            float maxRadius{0.0f};
            float timetolive{0.0f};
            float lifetime{0.0f};

            Particle(float dx, float dy, float v, float r, float ttl) : dirX(dx), dirY(dy), speed(v), radius(r), maxRadius(r), timetolive(ttl), lifetime(ttl) {}
        };
        
        std::vector<Particle> particles;
        float m_lifetime{0.0f};

        void randomizeColor();
    };

} // namespace tdg::core

#endif // HIT_SPARK_VFX_HPP