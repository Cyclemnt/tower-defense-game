#ifndef AUTO_WAVE_SOURCE_HPP
#define AUTO_WAVE_SOURCE_HPP

#include <random>
#include <cmath>
#include "iWaveSource.hpp"

/**
 * @class AutoWaveSource
 * @brief Procedurally generates waves with increasing difficulty.
 *
 * Each wave’s size increases according to a power function.
 * Creature types are chosen randomly using a weighted distribution.
 */
class AutoWaveSource : public IWaveSource {
private:
    std::mt19937 gen{ std::random_device{}() }; ///< Random number generator
    std::discrete_distribution<int> dist{490, 10, 320, 10, 165, 5}; ///< Weighted creature distribution

    const float waveSizeCoef = 1.3f;
    const float spawnInterval = 1.0f;
    const float waveDelay = 10.0f;

public:
    [[nodiscard]] bool hasMoreWaves() const noexcept override;
    WaveData nextWave() override;
};

#endif // AUTO_WAVE_SOURCE_HPP
