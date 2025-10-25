#ifndef AUTO_WAVE_SOURCE_HPP
#define AUTO_WAVE_SOURCE_HPP

#include <random>
#include <cmath>
#include "iWaveSource.hpp"

class AutoWaveSource : public IWaveSource {
private:
    std::mt19937 gen{std::random_device{}()};
    std::discrete_distribution<int> dist{490, 10, 320, 10, 165, 5}; // ‰
    int waveIndex = 0;
    const int maxWaves = 10;
    const float waveSizeCoef = 1.3f;

    constexpr static float spawnInterval = 1.0f;
    constexpr static float waveDelay = 10.0f;

public:
    bool hasMoreWaves() const override;
    WaveData nextWave() override;
};

#endif // AUTO_WAVE_SOURCE_HPP
