#include "../../include/waves/autoWaveSource.hpp"

bool AutoWaveSource::hasMoreWaves() const noexcept {
    return waveIndex < wavesQuantity;
}

WaveData AutoWaveSource::nextWave() {
    if (!hasMoreWaves()) return {};

    ++waveIndex;
    const int totalUnits = static_cast<int>(2 + std::pow(waveIndex, waveSizeCoef));

    WaveData wave;
    wave.delay = waveDelay;
    wave.spawns.reserve(static_cast<std::size_t>(totalUnits));

    for (int i = 0; i < totalUnits; ++i)
        wave.spawns.push_back({ static_cast<Creature::Type>(dist(gen)), spawnInterval });

    return wave;
}
