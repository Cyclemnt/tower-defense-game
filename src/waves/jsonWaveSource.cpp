#include "../../include/waves/jsonWaveSource.hpp"

JsonWaveSource::JsonWaveSource(const std::string& file)
    : loader(file)
{
    wavesQuantity = loader.getWavesQuantity();
}

bool JsonWaveSource::hasMoreWaves() const noexcept {
    return loader.hasMore();
}

WaveData JsonWaveSource::nextWave() {
    waveIndex = loader.getWaveIndex();
    return loader.next();
}
