#include "../../include/waves/jsonWaveSource.hpp"

JsonWaveSource::JsonWaveSource(const std::string& filename)
    : loader(std::make_unique<JsonWaveLoader>(filename)) {}

bool JsonWaveSource::hasNextWave() const { return loader->hasNextWave(); }

std::vector<WaveEntry> JsonWaveSource::nextWave() {
    auto jsonEntries = loader->getNextWave();
    std::vector<WaveEntry> entries;
    entries.reserve(jsonEntries.size());
    for (auto& e : jsonEntries)
        entries.push_back({ e.type, e.count });
    return entries;
}
