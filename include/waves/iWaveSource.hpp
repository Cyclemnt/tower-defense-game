#ifndef I_WAVE_SOURCE_HPP
#define I_WAVE_SOURCE_HPP

#include <vector>
#include "creatures/creature.hpp"

/// @struct SpawnCommand
/// @brief Describes a single creature spawn event within a wave.
struct SpawnCommand {
    Creature::Type type; ///< Type of creature to spawn
    float delay = 0.0f;  ///< Delay (seconds) before spawning the next one
};

/// @struct WaveData
/// @brief Represents a complete wave, including spawn sequence and initial delay.
struct WaveData {
    std::vector<SpawnCommand> spawns; ///< All creatures to spawn
    float delay = 0.0f;               ///< Delay before the wave begins
};

/**
 * @class IWaveSource
 * @brief Abstract interface for all wave data sources.
 *
 * Implementations define how waves are generated (procedurally or from files).
 */
class IWaveSource {
protected:
    size_t waveIndex = 0;
    size_t wavesQuantity = 100000;
    
public:
    virtual ~IWaveSource() = default;

    /// @brief Returns true if more waves are available.
    [[nodiscard]] virtual bool hasMoreWaves() const noexcept = 0;

    /// @brief Returns the next wave definition.
    virtual WaveData nextWave() = 0;

    [[nodiscard]] size_t getWaveIndex() const noexcept { return waveIndex; }
    [[nodiscard]] size_t getWavesQuantity() const noexcept { return wavesQuantity; }
};

#endif // I_WAVE_SOURCE_HPP
