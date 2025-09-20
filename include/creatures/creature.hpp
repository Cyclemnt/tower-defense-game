#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "../map/tile.hpp"
#include <vector>

/// @brief Represents a creature in the game, capable of moving along a path, taking damage, and carrying cores.
class Creature {
private:
    // --- Creature Specifications ---
    int health;           ///< Health of the creature.
    int shield;           ///< Shield of the creature.
    int speed;            ///< Speed of the creature, used to determine movement.

    // --- Core Carrying ---
    int coresCarried;     ///< Number of cores the creature is currently carrying.

    // --- Path Information ---
    std::vector<Tile*> path;      ///< The path the creature will follow (a sequence of tiles).
    int pathIndex;                ///< Current index on the path (indicating the creature's position).

    bool alive;           ///< Boolean flag indicating whether the creature is alive or dead.

public:
    /// @brief Constructs a new creature with specified health, shield, and speed.
    /// @param hp Initial health of the creature.
    /// @param sh Initial shield of the creature.
    /// @param spd Speed of the creature.
    Creature(int hp, int sh, float spd);

    /// @brief Default destructor.
    virtual ~Creature() = default;
    
    // --- State ---

    /// @brief Checks if the creature is alive.
    /// @return True if the creature's health is greater than 0, false otherwise.
    bool isAlive() const;

    /// @brief Gets the current health of the creature.
    /// @return The health value of the creature.
    int getHealth() const;

    /// @brief Gets the current shield value of the creature.
    /// @return The shield value of the creature.
    int getShield() const;

    /// @brief Gets the number of cores the creature is carrying.
    /// @return The amount of cores the creature has.
    int getCoresCarried() const;

    // --- Path Handling ---
    
    /// @brief Sets the path for the creature to follow.
    /// @param p The path (a vector of tiles) that the creature will follow.
    void setPath(const std::vector<Tile*>& p);

    /// @brief Gets the current tile the creature is on.
    /// @return Pointer to the current tile in the path.
    Tile* getCurrentTile() const;

    /// @brief Gets the next tile the creature will move to.
    /// @return Pointer to the next tile in the path, or nullptr if there are no more tiles.
    Tile* getNextTile() const;

    // --- Actions ---

    /// @brief Updates the creature's state, moving it along its path if possible.
    virtual void update();

    /// @brief Reduces the creature's health and shield when it takes damage.
    /// @param dmg Amount of damage to apply to the creature.
    virtual void takeDamage(int dmg);

    /// @brief Attempts to pick up a core from the environment.
    virtual void stealCore();

    /// @brief Drops all the cores the creature is carrying (when it dies).
    /// @return The number of cores dropped by the creature.
    virtual int dropCores();

    // --- Debug ---

    /// @brief Gets the name or type of the creature (for debugging purposes).
    /// @return A string representing the type or name of the creature.
    virtual std::string getTypeName() const;
};

#endif // CREATURE_HPP
