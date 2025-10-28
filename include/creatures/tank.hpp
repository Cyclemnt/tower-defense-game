#ifndef TANK_HPP
#define TANK_HPP

#include "creature.hpp"

/**
 * @class Tank
 * @brief A slow, heavily armored enemy.
 *
 * The Tank is a durable enemy unit with high health and strong shields,
 * designed to absorb significant amounts of damage and protect weaker enemies.
 *
 * Boosted Tanks are even more resistant and yield greater rewards.
 */
class Tank final : public Creature {
public:
    /// @brief Constructs a Tank.
    /// @param boosted_ Whether this Tank is a boosted variant.
    explicit Tank(bool boosted_ = false) noexcept;

    ~Tank() override = default;

private:
    /// @brief Returns the texture name for this creature.
    /// @param frame The animation frame index.
    [[nodiscard]] std::string getTextureName(int frame) const override;
};

#endif // TANK_HPP
