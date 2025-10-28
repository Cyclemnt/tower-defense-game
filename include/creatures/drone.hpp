#ifndef DRONE_HPP
#define DRONE_HPP

#include "creature.hpp"

/**
 * @class Drone
 * @brief A balanced mid-tier enemy.
 *
 * The Drone is a versatile enemy type with average speed and durability.
 * It serves as the core unit in most waves and represents the standard difficulty baseline.
 *
 * Boosted Drones have stronger shields and better loot.
 */
class Drone final : public Creature {
public:
    /// @brief Constructs a Drone.
    /// @param boosted_ Whether this Drone is a boosted variant.
    explicit Drone(bool boosted_ = false) noexcept;

    ~Drone() override = default;

private:
    /// @brief Returns the texture name for this creature.
    /// @param frame The animation frame index.
    [[nodiscard]] std::string getTextureName(int frame) const override;
};

#endif // DRONE_HPP
