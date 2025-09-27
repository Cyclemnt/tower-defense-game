#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "../map/tile.hpp"
#include <vector>
#include <array>

/**
 * @class Creature
 * @brief Base class for enemy units.
 *
 * A Creature represents an enemy that follows a path through the map.
 * Creatures have health, shields, speed, and may carry stolen cores.
 * They can move, take damage, die, and drop cores upon death.
 */
class Creature {
private:
    // --- Creature position ---
    float posX;
    float posY;

    // --- Creature Specifications ---
    float health;   ///< Health of the creature.
    float shield;   ///< Shield of the creature.
    float speed;    ///< Speed of the creature in tile per second, used to determine movement.

    // --- Loot quantities ---
    int au;     ///< Amount of Au dropped when killed.
    int ag;     ///< Amount of Ag dropped when killed.
    int cu;     ///< Amount of Cu dropped when killed.

    // --- Core Carrying ---
    int coresCarried;           ///< Number of cores the creature is currently carrying.
    int coresCapacity;          ///< Number of cores the creature can carry.

    // --- Path Information ---
    std::vector<Tile*> path;    ///< The path the creature will follow (a sequence of tiles).
    int pathIndex;              ///< Current index on the path (indicating the creature's position).

    bool alive;     ///< Boolean flag indicating whether the creature is alive or dead.

public:
    /// @brief Constructs a new creature with specified health, shield, and speed.
    /// @param hp Initial health of the creature.
    /// @param sh Initial shield of the creature.
    /// @param spd Speed of the creature.
    Creature(float hp, float sh, float spd, int coresCapacity_, int au_, int ag_, int cu_);

    /// @brief Default destructor.
    virtual ~Creature() = default;
    
    // --- State ---

    /// @brief Checks if the creature is alive.
    /// @return True if the creature's health is greater than 0, false otherwise.
    bool isAlive() const;

    /// @brief Gets the current health of the creature.
    /// @return The health value of the creature.
    float getHealth() const;

    /// @brief Gets the current shield value of the creature.
    /// @return The shield value of the creature.
    float getShield() const;

    /// @brief Gets the number of cores the creature is carrying.
    /// @return The amount of cores the creature has.
    int getCoresCarried() const;

    // --- Path Handling ---
    
    /// @brief Sets the path for the creature to follow.
    /// @param p The path (a vector of tiles) that the creature will follow.
    void setPath(const std::vector<Tile*>& p);

    /// @brief Gets the current creature coordinates.
    /// @return an array of x and y.
    std::array<float, 2> getPosition() const;

    /// @brief Gets the current tile the creature is on.
    /// @return Pointer to the current tile in the path.
    Tile* getCurrentTile() const;

    /// @brief Gets the next tile the creature will move to.
    /// @return Pointer to the next tile in the path, or nullptr if there are no more tiles.
    Tile* getNextTile() const;

    /// @brief Gets the last tile on the creature's path.
    /// @return Pointer to the last tile on the path.
    Tile* getDestinationTile() const;

    // --- Actions ---

    /// @brief Updates the creature's state, moving it along its path if possible.
    /// @param deltaTime Time elapsed since last update.
    virtual void update(float deltaTime);

    /// @brief Reduces the creature's health and shield when it takes damage.
    /// @param dmg Amount of damage to apply to the creature.
    virtual void takeDamage(float dmg);

    /// @brief Attempts to pick up a core from the environment.
    /// @param amount Quantity of cores taken.
    virtual void stealCores(int amount);

    /// @brief Drops all the cores the creature is carrying (when it dies).
    /// @return The number of cores dropped by the creature.
    virtual int dropCores();

    // --- Debug ---

    /// @brief Gets the name or type of the creature (for debugging purposes).
    /// @return A string representing the type or name of the creature.
    virtual std::string getTypeName() const = 0;
};

#endif // CREATURE_HPP
