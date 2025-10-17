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

    /** 
     * @brief Available creature types for waves (shared and immutable). 
     */
    inline static const std::vector<CreatureType> types = {
        CreatureType::Minion,
        CreatureType::Drone,
        CreatureType::Tank
    };

private:
    int currentWave = 0;          ///< Current wave index
    float spawnTimer = 0.0f;      ///< Timer used to control spawn intervals
    float spawnInterval = 0.5f;   ///< Time delay between individual spawns

    std::vector<WaveEntry> pendingWave; ///< Composition of the current wave
    int pendingTypeIndex = 0;     ///< Index of the current creature type being spawned
    int pendingUnitCount = 0;     ///< Remaining units to spawn for the current type

    int maxWaves = 10;            ///< Maximum number of waves before the game stops generating more
    bool waveFinished = false;    ///< True if the current wave has ended (all enemies defeated)
    float timeSinceWaveEnd = 0.0f;///< Time elapsed since the end of the last wave

public:
    /**
     * @brief Default constructor.
     * Initializes internal counters and random seed for wave generation.
     */
    WaveManager();

    /**
     * @brief Updates the current wave state over time.
     *
     * This method is called each frame by Game::update().
     * It handles progressive spawning, waits between waves,
     * and triggers new wave generation when the previous one is complete.
     *
     * @param dt Time elapsed since the last update (delta time)
     * @param game Reference to the main Game instance
     */
    void update(float dt, Game& game);

    /**
     * @brief Generates the next wave of enemies based on the wave number.
     *
     * Each wave increases in total "weight", which determines
     * how many and what type of creatures will appear.
     */
    void generateNextWave();

    /**
     * @brief Returns the index of the current wave.
     * @return The current wave number.
     */
    int getCurrentWave() const;

    /**
     * @brief Sets the maximum number of waves allowed.
     * @param max The number of waves after which no new waves will be generated.
     */
    void setMaxWaves(int max);
};

#endif // WAVE_MANAGER_HPP
