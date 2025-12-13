#ifndef HIT_SPARK_VFX_HPP
#define HIT_SPARK_VFX_HPP

#include <vector>
#include "core/vfxs/vfx.hpp"

namespace tdg::core {

    class HitSparkVFX final : public VFX {
    private:
        struct Particle {
            float vx{0.0f}, vy{0.0f};
            float speed{0.0f};
            float radius{0.0f};
            float timetolive{0.0f};
        };
        
        std::vector<Particle> particles;

        void randomizeColor();
        void randomizeJitter();

    public:
        HitSparkVFX(unsigned int level, float x1, float y1);

        void update(float dt) override;
    };

} // namespace tdg::core

#endif // HIT_SPARK_VFX_HPP