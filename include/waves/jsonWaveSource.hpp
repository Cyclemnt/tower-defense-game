#ifndef JSON_WAVE_SOURCE_HPP
#define JSON_WAVE_SOURCE_HPP

#include "iWaveSource.hpp"
#include "jsonWaveLoader.hpp"

class JsonWaveSource : public IWaveSource {
private:
    JsonWaveLoader loader;

public:
    explicit JsonWaveSource(const std::string& file);
    bool hasMoreWaves() const override;
    WaveData nextWave() override;
};

#endif // JSON_WAVE_SOURCE_HPP
