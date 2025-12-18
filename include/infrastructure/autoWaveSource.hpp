#ifndef AUTO_WAVE_SOURCE_HPP
#define AUTO_WAVE_SOURCE_HPP

#include <random>
#include "core/interfaces/iWaveSource.hpp"

namespace tdg::infra {
    
    class AutoWaveSource final : public core::IWaveSource {
    public:
        AutoWaveSource();

        unsigned int waveCount() const override; // To get the number of waves
        void setLevel(unsigned int level) override; // To set the level of the waves
        core::WaveData loadWave(unsigned int waveIndex) const override; // To generate the description of a wave
        
    private:
        mutable std::mt19937 gen{ std::random_device{}() }; ///< Random number generator
        mutable std::discrete_distribution<int> creatureTypeDist{200, 200, 100}; ///< Weighted creature type distribution
        mutable std::discrete_distribution<int> creatureLevelDist{300, 200}; ///< Weighted creature level distribution

        float m_difficultyCoefficient{1.3};
        std::optional<unsigned int> m_waveCount;

        const float m_spawnInterval{1.0f};
        const float m_waveInterval{10.0f};
    };

} // namespace tdg::infra

#endif // AUTO_WAVE_SOURCE_HPP