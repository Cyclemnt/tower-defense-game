#ifndef JSON_WAVE_LOADER_HPP
#define JSON_WAVE_LOADER_HPP

#include <vector>
#include <string>
#include "creatures/creature.hpp"
#include "iWaveSource.hpp"

class JsonWaveLoader {
private:
    struct InternalWave {
        int waveNumber;
        float delay; // seconds to wait before starting wave
        std::vector<SpawnCommand> spawns;
    };

    std::vector<InternalWave> waves;
    size_t index = 0;

    CreatureType parseType(const std::string& name) const;
    void parseFile(const std::string& filename);

public:
    explicit JsonWaveLoader(const std::string& filename);
    bool hasMore() const;
    WaveData next();
};

#endif // JSON_WAVE_LOADER_HPP
