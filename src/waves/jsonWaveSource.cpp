#include "../../include/waves/jsonWaveSource.hpp"

JsonWaveSource::JsonWaveSource(const std::string& file)
    : loader(file) {}

bool JsonWaveSource::hasMoreWaves() const {
    return loader.hasMore();
}

WaveData JsonWaveSource::nextWave() {
    return loader.next();
}
