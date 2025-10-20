#ifndef JSON_WAVE_LOADER_HPP
#define JSON_WAVE_LOADER_HPP

#include <vector>
#include <string>
#include <memory>
#include "creatures/creature.hpp"

class JsonWaveLoader {
private:
    struct WaveGroup {
        CreatureType type;
        int count;
        int intervalMs;
    };

    struct WaveData {
        int waveNumber;
        int startDelayMs;
        std::vector<WaveGroup> groups;
    };

    std::vector<WaveData> timeline;
    size_t currentWaveIndex = 0;

    CreatureType parseCreatureType(const std::string& name) const;
    void loadJsonFile(const std::string& filename);

public:
    struct WaveEntry {
        CreatureType type;
        int count;
    };

    explicit JsonWaveLoader(const std::string& filename);
    bool hasNextWave() const;
    std::vector<WaveEntry> getNextWave();
};

#endif // JSON_WAVE_LOADER_HPP
