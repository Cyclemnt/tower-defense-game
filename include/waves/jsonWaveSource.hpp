#ifndef JSON_WAVE_SOURCE_HPP
#define JSON_WAVE_SOURCE_HPP

#include "iWaveSource.hpp"
#include "jsonWaveLoader.hpp"

class JsonWaveSource : public IWaveSource {
private:
    std::unique_ptr<JsonWaveLoader> loader;

public:
    explicit JsonWaveSource(const std::string& filename);

    bool hasNextWave() const override;

    std::vector<WaveEntry> nextWave() override;
};

#endif // JSON_WAVE_SOURCE_HPP
