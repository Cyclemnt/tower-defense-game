#ifndef TOWER_HPP
#define TOWER_HPP

#include "creatures/creature.hpp"
#include "map/tile.hpp"
#include <string>
#include <vector>
#include <array>
#include <memory>

/**
 * @class Tower
 * @brief Base class for all towers in the tower defense game.
 *
 * A Tower is placed on an OpenZone tile by the player. Towers have a cost,
 * stats such as damage, range, and fire rate, and can optionally deal
 * area damage. Towers automatically search for and attack enemies in range,
 * and can be upgraded to improve their stats.
 */
class Tower {
protected:
    int x;              ///< X coordinate on the map grid.
    int y;              ///< Y coordinate on the map grid.

    int priceAu;        ///< Gold cost (Au) to build the tower.
    int priceAg;        ///< Silver cost (Ag) to build the tower.
    int priceCu;        ///< Copper cost (Cu) to build the tower.

    float damage;       ///< Damage dealt per attack.
    float range;        ///< Attack range (in tiles).
    float fireRate;     ///< Attacks per second.
    int level;          ///< Current upgrade level of the tower.

    float cooldown;     ///< Time left before the next attack.

    Creature* target;   ///< Target locked.

public:
    /// @brief Construct a new Tower object with given stats.
    /// @param x_ X coordinate on the map.
    /// @param y_ Y coordinate on the map.
    /// @param au Gold cost to build the tower.
    /// @param ag Silver cost to build the tower.
    /// @param cu Copper cost to build the tower.
    /// @param dmg Base damage per attack.
    /// @param rng Attack range in tiles.
    /// @param rate Number of attacks per second (fire rate).
    Tower(int x_, int y_, int au, int ag, int cu, int dmg, float rng, float rate);

    /// Virtual destructor.
    virtual ~Tower() = default;

    // --- Getters ---

    /// @return X coordinate on the map grid.
    int getX() const;

    /// @return Y coordinate on the map grid.
    int getY() const;

    /// @return Current upgrade level of the tower.
    int getLevel() const;

    /// @return Attack damage of the tower.
    float getDamage() const;

    /// @return Attack range of the tower in tiles.
    float getRange() const;

    /// @return Fire rate (attacks per second).
    float getFireRate() const;

    /// @return The price of the tower.
    std::array<int, 3> getPrice() const;
    
    /// @return The target of the tower.
    const Creature* getTarget() const;

    // --- Actions ---

    /// @brief Update tower logic each tick.
    /// Checks cooldown and searches for enemies within range. If a valid
    /// target is found, the tower attacks and resets its cooldown.
    /// @param creatures List of all creatures currently on the map.
    /// @param deltaTime Time elapsed since last update.
    virtual void update(float deltaTime, const std::vector<std::unique_ptr<Creature>>& creatures);

    /// @brief Attack a single creature target.
    /// @param target Pointer to the target creature.
    virtual void attack(Creature* target);
    
    /// @brief Selecting the best target among the creatures.
    /// Selects the strongest creature whithin range.
    /// @param creatures List of all creatures currently on the map.
    virtual Creature* selectTarget(const std::vector<std::unique_ptr<Creature>>& creatures);

    /// @brief Upgrade the tower.
    /// Increases stats such as damage, range, and fire rate. The upgrade
    /// rules may be overridden in derived classes for specific behaviors.
    virtual void upgrade();

    // --- Debug ---

    /// @brief Get the type name of the tower (for debug).
    /// @return String representing the type of the tower.
    virtual std::string getTypeName() const = 0;
};


#endif // TOWER_HPP
