#ifndef WAVE_MANAGER_HPP
#define WAVE_MANAGER_HPP

#include <memory>
#include "iWaveSource.hpp"
class Game;

/**
 * @class WaveManager
 * @brief Handles the spawning and timing of enemy waves during the game.
 *
 * The WaveManager retrieves wave data from an IWaveSource (automatic or JSON-based)
 * and controls the timing of creature spawns in each wave. It ensures correct pacing
 * between waves and synchronizes with the game's creature list.
 */
class WaveManager {
private:
    Game& game; ///< Reference to the current game
    std::unique_ptr<IWaveSource> source; ///< Source providing wave data
    WaveData activeWave;                 ///< Currently active wave
    size_t spawnIndex = 0;               ///< Current spawn index in the wave
    float timer = 0.0f;                  ///< Countdown until next spawn or wave
    bool inWave = false;                 ///< Flag indicating if currently in a wave

public:
    explicit WaveManager(std::unique_ptr<IWaveSource> src, Game& game_) noexcept;

    /// @brief Updates wave progression and spawns creatures when needed.
    void update(float dt);

    /// @brief Returns wether the wave is complete.
    [[nodiscard]] bool isWaveComplete() const noexcept;

    /// @brief Returns the current wave number.
    [[nodiscard]] size_t getWaveNumber() const noexcept;

    /// @brief Returns the quantity of waves in this level.
    [[nodiscard]] size_t getWavesQuantity() const noexcept;

    /// @brief Returns the time remaining before next wave.
    [[nodiscard]] float getTimeBeforeNext() const noexcept;
    
    /// @brief Returns wether the waves are over.
    [[nodiscard]] bool isEnded() const noexcept;
};

#endif // WAVE_MANAGER_HPP
