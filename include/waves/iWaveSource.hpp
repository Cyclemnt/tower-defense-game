#ifndef IWAVE_SOURCE_HPP
#define IWAVE_SOURCE_HPP

#include <vector>
#include "creatures/creature.hpp"

struct WaveEntry {
    CreatureType type;
    int count;
};

class IWaveSource {
public:
    virtual ~IWaveSource() = default;
    virtual bool hasNextWave() const = 0;
    virtual std::vector<WaveEntry> nextWave() = 0;
};

#endif // IWAVE_SOURCE_HPP
