#ifndef LASER_HPP
#define LASER_HPP

#include <SFML/System/Vector2.hpp>
#include "tower.hpp"

/**
 * @class Laser
 * @brief Continuous-damage tower that increases power while maintaining lock on a target.
 */
class Laser final : public Tower {
private:
    float baseDamage = 0.1f;  ///< Damage at start of lock.
    float damageScale = 1.0f; ///< Scales up over lock duration.
    float lockTime = 0.0f;    ///< Time spent locked on target.

public:
    explicit Laser(sf::Vector2i position_) noexcept;
    ~Laser() override = default;

    void update(float deltaTime, const std::vector<std::unique_ptr<Creature>>& creatures) override;

protected:
    [[nodiscard]] std::string getTextureName(int frame) const override;
};

#endif // LASER_HPP
