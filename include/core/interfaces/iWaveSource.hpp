#ifndef I_WAVE_SOURCE_HPP
#define I_WAVE_SOURCE_HPP

#include <vector>
#include <string>
#include <optional>
#include "core/creatures/creature.hpp"

namespace tdg::core {

    struct SpawnEntry {
        float delay{0};
        std::optional<unsigned int> spawnEntrance;
        Creature::Type enemyType;
    };

    struct WaveData {
        float startDelay{0};
        std::vector<SpawnEntry> spawns;
    };

    /// @brief Provides wave definitions for a level (scripted or procedural).
    class IWaveSource {
    public:
        virtual ~IWaveSource() = default;
        virtual unsigned int waveCount() const = 0;
        virtual WaveData loadWave(unsigned int waveIndex) const = 0;
    };

} // namespace tdg::core

#endif // I_WAVE_SOURCE_HPP