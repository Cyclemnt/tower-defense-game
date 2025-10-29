#ifndef JSON_WAVE_SOURCE_HPP
#define JSON_WAVE_SOURCE_HPP

#include "iWaveSource.hpp"
#include "jsonWaveLoader.hpp"

/**
 * @class JsonWaveSource
 * @brief Loads wave definitions from a JSON file.
 *
 * This implementation delegates parsing to JsonWaveLoader.
 */
class JsonWaveSource : public IWaveSource {
private:
    JsonWaveLoader loader; ///< Internal JSON wave loader

public:
    explicit JsonWaveSource(const std::string& file);

    [[nodiscard]] bool hasMoreWaves() const noexcept override;
    WaveData nextWave() override;
};

#endif // JSON_WAVE_SOURCE_HPP
