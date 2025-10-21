#ifndef AUTO_WAVE_SOURCE_HPP
#define AUTO_WAVE_SOURCE_HPP

#include <random>
#include <cmath>
#include "iWaveSource.hpp"

class AutoWaveSource : public IWaveSource {
private:
    std::mt19937 gen{std::random_device{}()};
    std::discrete_distribution<int> dist{50, 33, 17};
    int currentWave = 0;
    int maxWaves = 10;
    float waveSizeCoef = 1.3f;

public:
    bool hasNextWave() const override;

    std::vector<WaveEntry> nextWave() override;
};

#endif // AUTO_WAVE_SOURCE_HPP
