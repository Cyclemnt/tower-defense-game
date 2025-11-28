#ifndef MORTAR_HPP
#define MORTAR_HPP

#include "core/towers/tower.hpp"

namespace tdg::core {

    class Mortar final : public Tower {
    private:
        struct Shell {
            float curX, curY;
            float endX, endY;
            bool active = true;

            // Shell(float curX, float curY, float endX, float endY)
            //     : curX(curX), curY(curY), endX(endX), endY(endY) {}
        };

        std::vector<Shell> m_shells;
        float m_shellSpeed = 4.0f;
        float m_shellExplosionRadius = 0.6f;

    public:
        explicit Mortar(int x, int y) noexcept;
        ~Mortar() override = default;

        void update(float dt, const std::vector<CreaturePtr>& creatures) override;
    };

} // namespace tdg::core

#endif // MORTAR_HPP