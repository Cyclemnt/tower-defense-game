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
#include "waves/waveManager.hpp"

/**
 * @enum PlaceTowerResult
 * @brief Represents the result of attempting to place a tower on the map.
 */
enum class PlaceTowerResult {
    Success,       ///< The tower was placed successfully.
    NotBuildable,  ///< The target tile cannot host a tower.
    Occupied,      ///< The tile is already occupied.
    NotAffordable  ///< The player cannot afford the tower cost.
};

/**
 * @class Game
 * @brief Central class managing all gameplay systems.
 *
 * The Game class coordinates all subsystems:
 * - Map loading and tile management.
 * - Pathfinding for creatures.
 * - Creature spawning and behavior.
 * - Tower placement, updates, and interactions.
 * - Player resources (materials and cores).
 * - Wave management and game progression.
 */
class Game {
private:
    // --- Core world components ---
    Map map;               ///< The game map containing tiles and zones.
    Pathfinder pathfinder; ///< A* pathfinding system.

    // --- Player state ---
    Player player; ///< Player materials, actions, and upgrades.
    Cores cores;   ///< Player's cores: safe, stolen, and lost counts.

    // --- Entities ---
    std::vector<std::unique_ptr<Creature>> creatures; ///< Active enemy units.
    std::vector<std::unique_ptr<Tower>> towers;       ///< Active player towers.
    std::vector<std::unique_ptr<VisualEffect>> visualEffects; ///< Active VFX.

    // --- Wave control ---
    std::unique_ptr<WaveManager> waveManager; ///< Wave and timing system.

    // --- Game state ---
    unsigned long tick = 0; ///< Simulation tick counter.
    bool paused = false;    ///< Whether the game is paused.

public:
    /// @brief Constructs a new Game instance and initializes all systems.
    Game();

    // --- Accessors ---
    [[nodiscard]] const Map& getMap() const noexcept { return map; }
    [[nodiscard]] const std::vector<std::unique_ptr<Creature>>& getCreatures() const noexcept { return creatures; }
    [[nodiscard]] const std::vector<std::unique_ptr<Tower>>& getTowers() const noexcept { return towers; }
    [[nodiscard]] unsigned long getTick() const noexcept { return tick; }
    [[nodiscard]] bool isPaused() const noexcept { return paused; }
    void setPaused(bool value) noexcept { paused = value; }
    [[nodiscard]] const Player& getPlayer() const noexcept { return player; }
    [[nodiscard]] const Cores& getCores() const noexcept { return cores; }
    [[nodiscard]] const std::vector<std::unique_ptr<VisualEffect>>& getVisualEffects() const noexcept { return visualEffects; }

    // --- Entity management ---
    /// @brief Spawns a new creature of a given type and assigns it a path.
    /// @param type The type of creature to spawn.
    void spawnCreature(Creature::Type type);

    /// @brief Attempts to place a tower on the map.
    /// @param tower The tower instance to place.
    /// @return A result describing whether placement succeeded.
    PlaceTowerResult placeTower(std::unique_ptr<Tower> tower);

    /// @brief Sells and removes the tower at a given map position.
    /// @param position The tile coordinates where to sell the tower.
    void sellTowerAt(sf::Vector2i position);

    /// @brief Recomputes all creature paths (used after map changes).
    void updatePaths();

    // --- Simulation control ---
    /// @brief Advances the simulation by one tick.
    /// @param deltaTime Time since last update (in seconds).
    void update(float deltaTime);

    /// @brief Checks whether the player has lost all cores.
    [[nodiscard]] bool isGameOver() const noexcept;
};

#endif // GAME_HPP
