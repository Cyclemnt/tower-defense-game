#ifndef LASER_HPP
#define LASER_HPP

#include <string>
#include <memory>
#include <vector>
#include "tower.hpp"
class Creature;

/**
 * @class Laser
 * @brief Continuous damage tower.
 *
 * The Laser locks onto a target and deals damage over time,
 * increasing damage the longer it stays focused on the same enemy.
 */
class Laser : public Tower {
private:
    float damageScale;  ///< Damage multiplier increasing over time
    float lockTime;     ///< Time spent locked on the current target
    float baseDamage;   ///< Base damage before scaling

public:
    Laser(int x_, int y_);
    ~Laser();

    /// @brief Update tower logic each tick.
    /// - Decreases cooldown timer
    /// - Searches for enemies in range
    /// - Locks onto a target and applies continuous damage
    /// - Increases damage scaling if the same target is held
    /// @param deltaTime Time elapsed since last update
    /// @param creatures All creatures currently on the map
    void update(float deltaTime, const std::vector<std::unique_ptr<Creature>>& creatures) override;

    /// @return The type name of this tower ("Laser").
    std::string getTextureName(int frame) const override;
};

#endif // LASER_HPP
