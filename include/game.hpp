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
 * @class Game
 * @brief Central class managing gameplay systems (map, entities, waves, etc.).
 *
 * Game coordinates:
 * - Map, towers, creatures, pathfinding
 * - Player resources and cores
 * - Wave spawning and progression
 */
class Game {
public:
    /// @struct GameView
    /// @brief Lightweight read-only snapshot of game state for UI and HUD.
    struct View {
        const Materials::Quantities* playerBalance; ///< Player resources
        const Cores* cores;  ///< Core status
        int currentWave = 0; ///< Current wave number
        int totalWaves = 0;  ///< Total number of waves
        float timeBeforeNext = 0.0f; ///< Seconds before next wave
    };
    Player::State playerState = Player::State::None; ///< Player current possible action.

private:
    // --- Core world ---
    Map map; ///< The game map containing tiles.
    Pathfinder pathfinder; ///< A* pathfinding system.

    // --- Player state ---
    Player player; ///< Player, with its materials.
    Cores cores; ///< Player's cores: safe, stolen, and lost counts.

    // --- Entities ---
    std::vector<std::unique_ptr<Creature>> creatures; ///< Active enemy units.
    std::vector<std::unique_ptr<Tower>> towers; ///< Active player towers.
    std::vector<std::unique_ptr<VisualEffect>> visualEffects; ///< Active VFX.

    // --- Waves ---
    WaveManager waveManager; ///< Wave and timing system.

    // --- Time and state ---
    unsigned long tick = 0; ///< Simulation tick (frames) counter.
    unsigned int speed = 1; ///< Time acceleration coefficient.
    bool paused = false;    ///< Whether the game is paused.

public:
    /// @brief Constructs a new Game instance and initializes all systems.
    Game();

    /// @brief Constructs a new Game instance and initializes all systems.
    /// @param mapSource_ Source used to build the map.
    /// @param waveSource_ Source used to generate or load waves.
    /// @param initialCores Number of cores available at game start.
    Game(std::unique_ptr<IMapSource> mapSource_, std::unique_ptr<IWaveSource> waveManager, unsigned int initialCores);

    // --- Simulation control ---

    /// @brief Advances the simulation by one tick.
    /// @param deltaTime Time since last update (in seconds).
    void update(float deltaTime);

    [[nodiscard]] bool isPaused() const noexcept { return paused; }
    void setPaused(bool value) noexcept { paused = value; }

    /// @brief Checks whether the player has lost all cores.
    [[nodiscard]] bool isOver() const noexcept;
    [[nodiscard]] unsigned long getTick() const noexcept { return tick; }
    void accelerate() noexcept { speed = 8; }
    void resetSpeed() noexcept { speed = 1; }


    // --- Gameplay interface ---

    /// @brief Spawns a new creature of a given type and assigns it a path.
    /// @param type The type of creature to spawn.
    void spawnCreature(Creature::Type type);

    /// @brief Attempts to place a tower on the map.
    /// @param tower The tower instance to place.
    void tryPlaceTower(std::unique_ptr<Tower> tower);

    /// @brief Sells and removes the tower at a given map position.
    /// @param position The tile coordinates where to sell the tower.
    void trySellTower(sf::Vector2i position);

    // --- Access for rendering ---

    const Map& getMap() const noexcept { return map; }
    const std::vector<std::unique_ptr<Creature>>& getCreatures() const noexcept { return creatures; }
    const std::vector<std::unique_ptr<Tower>>& getTowers() const noexcept { return towers; }
    const std::vector<std::unique_ptr<VisualEffect>>& getVisualEffects() const noexcept { return visualEffects; }

    // --- Access for UI / HUD ---

    [[nodiscard]] std::unique_ptr<const Game::View> getView() const;

private:
    // --- Internal utilities ---

    /// @brief Recomputes all creature paths (used after map changes).
    void updatePaths();
};

#endif // GAME_HPP
