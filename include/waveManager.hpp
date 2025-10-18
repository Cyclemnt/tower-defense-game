#ifndef WAVE_MANAGER_HPP
#define WAVE_MANAGER_HPP

#include <vector>
#include <memory>
#include "creatures/creature.hpp"

class Game;

/**
 * @brief Handles the creation, timing, and progression of enemy waves.
 *
 * The WaveManager controls when new waves are generated, how enemies
 * are spawned over time, and ensures progressive difficulty scaling.
 * It also manages cooldowns between waves and can limit the total number of waves.
 */
class WaveManager {
public:
    /**
     * @brief Represents a type of creature and the number of units to spawn.
     */
    struct WaveEntry {
        CreatureType type;  ///< Type of creature to spawn
        int count;          ///< Number of units of this type in the wave
    };

public:
    WaveManager();  ///< Constructor

    void update(float dt, Game& game);      ///< Update wave state each frame
    void generateNextWave();                ///< Generate next wave of enemies
    int getCurrentWave() const;             ///< Get current wave index
    void setMaxWaves(int max);              ///< Set maximum allowed waves

    /**
     * @brief Check if the current wave has finished (no pending or active enemies)
     * @param game Reference to the game instance
     * @return True if wave is over, false otherwise
     */
    bool isWaveOver(const Game& game) const;

private:
    int currentWave = 0;          ///< Current wave index
    float spawnTimer = 0.0f;      ///< Timer for spawn intervals
    float spawnInterval = 0.5f;   ///< Time delay between individual spawns

    std::vector<WaveEntry> pendingWave; ///< Current wave composition
    int pendingTypeIndex = 0;     ///< Index of the type being spawned
    int pendingUnitCount = 0;     ///< Remaining units of current type

    float waveSizeCoef = 1.3f;   ///< Size coefficient for the waves
    int maxWaves = 10;            ///< Maximum number of waves
    bool waveFinished = false;    ///< True if the wave ended
    float timeSinceWaveEnd = 0.0f;///< Time since last wave ended
};

#endif // WAVE_MANAGER_HPP
