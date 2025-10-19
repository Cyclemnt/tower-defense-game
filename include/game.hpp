#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <memory>
#include "map/map.hpp"
#include "pathfinder.hpp"
#include "player.hpp"
#include "resources/cores.hpp"
#include "creatures/creature.hpp"
#include "towers/tower.hpp"
#include "visual-effects/visualEffect.hpp"
#include "waveManager.hpp"

enum class PlaceTowerResult {
    Success,
    NotBuildable,
    Occupied,
    NotAffordable
};

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
    Map map;                    ///< The game map containing tiles and zones
    Pathfinder pathfinder;      ///< Pathfinding system (A* search)

    Player player;              ///< Class that manages Player's actions
    Cores cores;                ///< Player's core resources (safe, stolen, lost)

    std::vector<std::unique_ptr<Creature>> creatures;   ///< List of active creatures
    std::vector<std::unique_ptr<Tower>> towers;         ///< List of placed towers
    std::vector<std::unique_ptr<VisualEffect>> visualEffects;

    WaveManager waveManager;

    unsigned long tick;                   ///< Current tick count (simulation time)
    bool paused;

public:
    /// @brief Construct a new Game object.
    Game();

    // --- Getters and setters ---
    
    const Map& getMap() const;
    const std::vector<std::unique_ptr<Creature>>& getCreatures() const;
    const std::vector<std::unique_ptr<Tower>>& getTowers() const;
    const unsigned long getTick() const;
    const bool isPaused() const;
    void setPaused(bool pause);
    void togglePause();
    const Player& getPlayer() const;
    const Cores& getCores() const;
    const std::vector<std::unique_ptr<VisualEffect>>& getVisualEffects() const;
    
    /// @brief Spawn a new creature and add it to the simulation.
    /// The creature will automatically be assigned a path from the entry
    /// to the exit using the Pathfinder.
    /// @param creature A unique pointer to the creature to be spawned.
    void spawnCreature(CreatureType type);

    /// @brief Place a new tower on the map.
    /// This method should check if the tile is buildable and if the player
    /// has enough resources before adding the tower.
    /// @param tower A unique pointer to the tower to be placed.
    /// @return The result of trying to place a tower (success or not).
    PlaceTowerResult placeTower(std::unique_ptr<Tower> tower);
    void sellTowerAt(int x, int y);
    void updatePaths();

    /// @brief Update the game state for one tick.
    /// - Moves creatures along their path.
    /// - Handles core stealing/loss logic.
    /// - Updates tower cooldowns and attacks.
    /// - Cleans up dead creatures.
    /// @param deltaTime Time elapsed since last update.
    void update(float deltaTime);

    /// @brief Check if the game is over.
    /// The game ends if all the cores are permanently lost.
    /// @return true if the game is over.
    /// @return false otherwise.
    bool isGameOver() const;
};

#endif // GAME_HPP
