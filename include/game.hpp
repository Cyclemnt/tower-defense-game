#ifndef GAME_HPP
#define GAME_HPP

#include "map/map.hpp"
#include "pathfinder.hpp"
#include "towers/tower.hpp"
#include "creatures/creature.hpp"
#include "player.hpp"
#include <vector>

/**
 * @brief The Game class is the central manager of the Tower Defense simulation.
 *
 * It handles the map, creatures, towers, resources, and the main game loop.
 * Responsibilities include:
 * - Spawning creatures and assigning them a path.
 * - Allowing the player to place towers (with resource checks).
 * - Updating the state of all entities each tick.
 * - Rendering a textual representation of the game state (before graphics).
 * - Managing player resources (Cores and Materials).
 */
class Game {
private:
    Map map;                          ///< The game map containing tiles and zones
    Pathfinder pathfinder;            ///< Pathfinding system (A* search)

    Player player;

    std::vector<std::unique_ptr<Creature>> creatures; ///< List of active creatures
    std::vector<std::unique_ptr<Tower>> towers;       ///< List of placed towers

    Cores cores;                      ///< Player's core resources (safe, stolen, lost)
    Materials materials;              ///< Player's construction resources

    int tick;                         ///< Current tick count (simulation time)

public:
    /// @brief Construct a new Game object.
    /// @param w Width of the map in tiles.
    /// @param h Height of the map in tiles.
    /// @param initialCores Number of cores initially stored in the base.
    Game(int w, int h, int initialCores);

    /// @brief Spawn a new creature and add it to the simulation.
    /// The creature will automatically be assigned a path from the entry
    /// to the exit using the Pathfinder.
    /// @param creature A unique pointer to the creature to be spawned.
    void spawnCreature(std::unique_ptr<Creature> creature);

    /// @brief Place a new tower on the map.
    /// This method should check if the tile is buildable and if the player
    /// has enough resources before adding the tower.
    /// @param tower A unique pointer to the tower to be placed.
    void placeTower(std::unique_ptr<Tower> tower);

    /// @brief Update the game state for one tick.
    /// - Moves creatures along their path.
    /// - Handles core stealing/loss logic.
    /// - Updates tower cooldowns and attacks.
    /// - Cleans up dead creatures.
    void update();

    /// @brief Render the current state of the game to the console.
    /// Displays the map grid and entity states for debugging purposes.
    void render() const;

    /// @brief Check if the game is over.
    /// The game ends if all the cores are permanently lost.
    /// @return true if the game is over.
    /// @return false otherwise.
    bool isGameOver() const;
};

#endif // GAME_HPP
