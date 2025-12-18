#ifndef I_WAVE_SOURCE_HPP
#define I_WAVE_SOURCE_HPP

#include <vector>
#include <optional>
#include "core/creatures/creature.hpp"

namespace tdg::core {

    // Structure to describe a spawn entry
    struct SpawnEntry {
        float delay{0};
        Creature::Type enemyType;
        unsigned int level;
        std::optional<unsigned int> spawnEntrance;
    };

    // Structure to describe a wave
    struct WaveData {
        float startDelay{0};
        std::vector<SpawnEntry> spawns;
    };

    /// @brief Provides wave definitions for a level (scripted or procedural).
    class IWaveSource {
    public:
        virtual ~IWaveSource() = default;
        virtual unsigned int waveCount() const = 0; // To get the number of waves
        virtual void setLevel(unsigned int level) = 0; // To set the level of the waves
        virtual WaveData loadWave(unsigned int waveIndex) const = 0; // To generate the description of a wave
    };

} // namespace tdg::core

#endif // I_WAVE_SOURCE_HPP