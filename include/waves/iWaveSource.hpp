#ifndef I_WAVE_SOURCE_HPP
#define I_WAVE_SOURCE_HPP

#include <vector>
#include "creatures/creature.hpp"

/// Represents one creature spawn order in a wave.
struct SpawnCommand {
    Creature::Type type;
    float delay = 0; // seconds to wait before spawning
};

/// Represents one complete wave definition.
struct WaveData {
    std::vector<SpawnCommand> spawns; // all creatures to spawn
    float delay = 0;                  // seconds to wait before starting wave
};

/// Interface for any wave generation source.
class IWaveSource {
public:
    virtual ~IWaveSource() = default;

    virtual bool hasMoreWaves() const = 0;
    virtual WaveData nextWave() = 0;
};

#endif // I_WAVE_SOURCE_HPP
