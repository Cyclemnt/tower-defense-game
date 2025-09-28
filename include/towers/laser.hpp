#ifndef LASER_HPP
#define LASER_HPP

#include "tower.hpp"

class Laser : public Tower
{
private:
    float damageScale;      ///< Coefficient applied to the base damage of the Laser, increases with time.
    float lockTime;         ///< Time locked on the same target.
    float baseDamage;       ///< Base damage of the Laser

public:
    Laser(int x_, int y_);
    ~Laser();

    /// @brief Update tower logic each tick.
    /// Checks cooldown and searches for enemies within range. If a valid
    /// target is found, the tower attacks and resets its cooldown.
    /// Increases the damage over time when targeting the same enemy
    /// @param creatures List of all creatures currently on the map.
    /// @param deltaTime Time elapsed since last update.
    void update(float deltaTime, const std::vector<std::unique_ptr<Creature>>& creatures) override;

    std::string getTypeName() const override;
};

#endif // LASER_HPP
