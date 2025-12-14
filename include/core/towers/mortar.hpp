#ifndef MORTAR_HPP
#define MORTAR_HPP

#include "core/towers/tower.hpp"

namespace tdg::core {

    class Mortar final : public Tower {
    public:
        explicit Mortar(int x, int y) noexcept;
        ~Mortar() override = default;

        void update(float dt, Events& events, const std::vector<CreaturePtr>& creatures) override;

        void upgrade() override;
        std::string spriteId() const noexcept override;

        void draw(IVideoRenderer& vidRenderer) const override;
        
    private:
        /// @brief Represents a projectile fired by the Mortar.
        struct Shell {
            float curX, curY;
            float endX, endY;
        };

        std::vector<Shell> m_shells;  ///< List of all active shells
        float m_shellSpeed = 4.0f;    ///< Shell speed in tile/s
        float m_shellExplosionRadius = 0.6f;  ///< Shell explosion radius in tile
    };

} // namespace tdg::core

#endif // MORTAR_HPP