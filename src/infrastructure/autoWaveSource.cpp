#include <cmath>
#include "infrastructure/autoWaveSource.hpp"
#include "core/creatures/creature.hpp"

namespace tdg::infra {
    
    AutoWaveSource::AutoWaveSource()
    {
        setLevel(1u);
    }

    unsigned int AutoWaveSource::waveCount() const {
        if (m_waveCount.has_value()) return m_waveCount.value();
        else return std::numeric_limits<unsigned int>::max();
    }

    void AutoWaveSource::setLevel(unsigned int level) {
        m_waveCount = std::nullopt;
        m_difficultyCoefficient = 1.0f + level / 10.0f;
    }

    core::WaveData AutoWaveSource::loadWave(unsigned int waveIndex) const {
        // Define the list of possible creature types
        std::vector<core::Creature::Type> creatureTypes = {
            core::Creature::Type::Minion,
            core::Creature::Type::Drone,
            core::Creature::Type::Tank,
        };

        core::WaveData wave;
        wave.startDelay = m_waveInterval; // Fixed interval between waves

        // Calculate the number of creatures in the wave, based on the difficulty coefficient
        unsigned int numCreaturesInWave = static_cast<unsigned int>(std::pow(waveIndex, m_difficultyCoefficient) * 5); // Base 5 creatures

        // Create the spawn entries for this wave
        for (unsigned int i = 0; i < numCreaturesInWave; ++i) {
            core::Creature::Type creatureType = creatureTypes[creatureTypeDist(gen)];
            unsigned int creatureLevel = creatureLevelDist(gen) + 1u;
            core::SpawnEntry se = {m_spawnInterval, creatureType, creatureLevel, std::nullopt};
            wave.spawns.push_back(se);
        }

        return wave;
    }

} // namespace tdg::infra
