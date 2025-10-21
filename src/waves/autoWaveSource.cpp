#include "../../include/waves/autoWaveSource.hpp"

bool AutoWaveSource::hasNextWave() const { return currentWave < maxWaves; }

std::vector<WaveEntry> AutoWaveSource::nextWave() {
    if (!hasNextWave()) return {};

    ++currentWave;
    std::vector<WaveEntry> wave;

    int totalUnits = static_cast<int>(2 + std::pow(currentWave, waveSizeCoef));
    for (int i = 0; i < totalUnits; ++i)
        wave.push_back({ static_cast<CreatureType>(dist(gen)), 1 });

    return wave;
}
