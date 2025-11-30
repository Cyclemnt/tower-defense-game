#ifndef I_WAVE_SOURCE_HPP
#define I_WAVE_SOURCE_HPP

#include <vector>
#include <string>

namespace tdg::core {

    struct SpawnEntry {
        float delay{0};
        std::string enemyType;
    };

    struct WaveData {
        float startDelay{0};
        std::vector<SpawnEntry> spawns;
    };

    /// @brief Provides wave definitions for a level (scripted or procedural).
    class IWaveSource {
    public:
        virtual ~IWaveSource() = default;
        virtual std::vector<WaveData> getWaves() const = 0;
    };

} // namespace tdg::core

#endif // I_WAVE_SOURCE_HPP