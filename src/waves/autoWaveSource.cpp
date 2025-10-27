#include "../../include/waves/autoWaveSource.hpp"

bool AutoWaveSource::hasMoreWaves() const { return waveIndex < maxWaves; }

WaveData AutoWaveSource::nextWave() {
    if (!hasMoreWaves()) return {};
    ++waveIndex;

    int totalUnits = static_cast<int>(2 + std::pow(waveIndex, waveSizeCoef));

    WaveData wave;
    wave.delay = waveDelay;
    wave.spawns.reserve(totalUnits);

    for (int i = 0; i < totalUnits; ++i) {
        wave.spawns.push_back({ static_cast<Creature::Type>(dist(gen)), spawnInterval });
    }

    return wave;
}
