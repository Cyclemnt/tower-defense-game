#ifndef JSON_WAVE_LOADER_HPP
#define JSON_WAVE_LOADER_HPP

#include <vector>
#include <string>
#include "creatures/creature.hpp"
#include "iWaveSource.hpp"

/**
 * @class JsonWaveLoader
 * @brief Minimal JSON parser to extract wave definitions.
 *
 * Parses a simplified JSON file describing wave sequences.
 * Each wave includes a delay, number, and enemy groups.
 */
class JsonWaveLoader {
private:
    struct InternalWave {
        int waveNumber = 0;
        float delay = 0.0f; ///< Delay before wave starts
        std::vector<SpawnCommand> spawns;
    };

    std::vector<InternalWave> waves; ///< Parsed wave list
    size_t waveIndex = 0;            ///< Current wave index

    Creature::Type parseType(const std::string& name) const noexcept;
    void parseFile(const std::string& filename);

public:
    explicit JsonWaveLoader(const std::string& filename);
    [[nodiscard]] bool hasMore() const noexcept;
    WaveData next();
    [[nodiscard]] size_t getWaveIndex() const noexcept { return waveIndex; }
    [[nodiscard]] size_t getWavesQuantity() const noexcept { return waves.size(); }
};

#endif // JSON_WAVE_LOADER_HPP
