#include <cmath>
#include "infrastructure/autoWaveSource.hpp"
#include "core/creatures/creature.hpp"

namespace tdg::infra {
    
    AutoWaveSource::AutoWaveSource(unsigned int waveCount)
        : m_waveCount(waveCount) {}

    unsigned int AutoWaveSource::waveCount() const {
        if (m_waveCount.has_value()) return m_waveCount.value();
        else return std::numeric_limits<unsigned int>::max();
    }

    core::WaveData AutoWaveSource::loadWave(unsigned int waveIndex) const {
        // Create a random engine for creature selection
        std::random_device rd;
        std::mt19937 rng(rd());

        // Define the list of possible creature types
        std::vector<core::Creature::Type> creatureTypes = {
            core::Creature::Type::Minion,
            core::Creature::Type::MinionB,
            core::Creature::Type::Drone,
            core::Creature::Type::DroneB,
            core::Creature::Type::Tank,
            core::Creature::Type::TankB
        };

        core::WaveData wave;
        wave.startDelay = m_waveInterval;  // Fixed interval between waves

        // Calculate the number of creatures in the wave, based on the difficulty coefficient
        unsigned int numCreaturesInWave = static_cast<unsigned int>(
            std::pow(m_difficultyCoefficient, waveIndex) * 5); // Base 5 creatures

        // Create the spawn entries for this wave
        for (unsigned int i = 0; i < numCreaturesInWave; ++i) {
            core::SpawnEntry se = {m_spawnInterval, std::nullopt, creatureTypes[rng() % creatureTypes.size()]};
            wave.spawns.push_back(se);
        }

        return wave;
    }

} // namespace tdg::infra
