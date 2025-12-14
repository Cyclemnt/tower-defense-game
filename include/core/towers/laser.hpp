#ifndef LASER_HPP
#define LASER_HPP

#include "core/towers/tower.hpp"

namespace tdg::core {

    class Laser final : public Tower {
    private:
        float m_baseDamage = 0.1f;  ///< Damage at start of lock.
        float m_damageScale = 1.0f; ///< Scales up over lock duration.
        float m_lockTime = 0.0f;    ///< Time spent locked on target.

        unsigned long m_tick{0u};   ///< Number of updates the object lived (for tick driven animation)

    public:
        explicit Laser(int x, int y) noexcept;
        ~Laser() override = default;

        void update(float dt, Events& events, const std::vector<CreaturePtr>& creatures) override;

        bool upgrade() override;
        std::string spriteId() const noexcept override;
    };
    
} // namespace tdg::core

#endif // LASER_HPP