#ifndef MORTAR_HPP
#define MORTAR_HPP

#include "tower.hpp"

/// @struct Shell
/// @brief Represents a projectile fired by the Mortar.
struct Shell {
    float posX, posY;           ///< Current projectile position
    float targetX, targetY;     ///< Target coordinates
    float damage;               ///< Damage on impact
    float speed = 4.0f;         ///< Speed in tiles/second
    float explosionRadius = 0.6f;   ///< Explosion radius in tiles
    bool active = true;         ///< Is the shell still flying?
};

/**
 * @class Mortar
 * @brief Area-of-effect tower type.
 *
 * The Mortar fires shells that travel through the map
 * and explode on impact, dealing damage in an area.
 */
class Mortar : public Tower {
private:
    std::vector<Shell> shells;  ///< All active projectiles fired by this mortar

public:
    Mortar(int x_, int y_);
    ~Mortar();

    const std::vector<Shell>& getShells() const;

    /// @brief Update tower logic each tick.
    /// - Fires new shells at enemies in range
    /// - Updates projectile positions
    /// - Applies area damage on impact
    /// @param deltaTime Time elapsed since last update
    /// @param creatures All creatures currently on the map
    void update(float deltaTime, const std::vector<std::unique_ptr<Creature>>& creatures) override;

    /// @return The type name of this tower ("Mortar").
    std::string getTypeName() const override;
};

#endif // MORTAR_HPP
