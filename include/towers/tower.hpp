#ifndef TOWER_HPP
#define TOWER_HPP

#include <string>
#include <vector>
#include "creatures/creature.hpp"
#include "map/tile.hpp"

/**
 * @class Tower
 * @brief Base class for all towers in the tower defense game.
 *
 * A Tower is placed on an OpenZone tile by the player. Each tower has
 * a purchase cost in materials, attack stats (damage, range, fire rate),
 * and can optionally deal area damage. Towers automatically search for
 * enemies within range and attack them when their cooldown is ready.
 *
 * Towers can also be upgraded to improve their stats.
 */
class Tower {
protected:
    int x;              ///< X coordinate on the map grid.
    int y;              ///< Y coordinate on the map grid.

    int priceAu;        ///< Gold cost (Au) to build the tower.
    int priceAg;        ///< Silver cost (Ag) to build the tower.
    int priceCu;        ///< Copper cost (Cu) to build the tower.

    int damage;         ///< Damage dealt per attack.
    float range;        ///< Attack range (in tiles).
    float fireRate;     ///< Attacks per second.
    bool areaDamage;    ///< Whether the attack affects an area (true) or a single target (false).
    int level;          ///< Current upgrade level of the tower.

    float cooldown;     ///< Time left before the next attack.

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
    /// @param area True if the tower deals area damage, false for single target.
    Tower(int x_, int y_, int au, int ag, int cu,
          int dmg, float rng, float rate, bool area);

    /// Virtual destructor.
    virtual ~Tower() = default;

    // --- Getters ---

    /// @return X coordinate on the map grid.
    int getX() const { return x; }

    /// @return Y coordinate on the map grid.
    int getY() const { return y; }

    /// @return Current upgrade level of the tower.
    int getLevel() const { return level; }

    /// @return Attack damage of the tower.
    int getDamage() const { return damage; }

    /// @return Attack range of the tower in tiles.
    float getRange() const { return range; }

    /// @return Fire rate (attacks per second).
    float getFireRate() const { return fireRate; }

    /// @return True if the tower deals area damage, false otherwise.
    bool isAreaDamage() const { return areaDamage; }

    // --- Actions ---

    /// @brief Update tower logic each tick.
    /// Checks cooldown and searches for enemies within range. If a valid
    /// target is found, the tower attacks and resets its cooldown.
    /// @param creatures List of all creatures currently on the map.
    virtual void update(std::vector<Creature*>& creatures);

    /// @brief Attack a single creature target.
    /// @param target Pointer to the target creature.
    virtual void attack(Creature* target);

    /// @brief Upgrade the tower.
    /// Increases stats such as damage, range, and fire rate. The upgrade
    /// rules may be overridden in derived classes for specific behaviors.
    virtual void upgrade();

    // --- Debug ---

    /// @brief Get the type name of the tower (for debug).
    /// @return String representing the type of the tower.
    virtual std::string getTypeName() const { return "Tower"; }
};


#endif // TOWER_HPP
