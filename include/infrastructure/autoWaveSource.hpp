#ifndef AUTO_WAVE_SOURCE_HPP
#define AUTO_WAVE_SOURCE_HPP

#include "core/interfaces/iWaveSource.hpp"
#include <random>

namespace tdg::infra {
    
    class AutoWaveSource : public core::IWaveSource {
    private:
        std::mt19937 gen{ std::random_device{}() }; ///< Random number generator
        mutable std::discrete_distribution<int> dist{490, 10, 320, 10, 165, 5}; ///< Weighted creature distribution

        float m_difficultyCoefficient{1.2};
        std::optional<unsigned int> m_waveCount;

        const float m_spawnInterval{1.0f};
        const float m_waveInterval{10.0f};

    public:
        AutoWaveSource(unsigned int waveCount);

        unsigned int waveCount() const override;
        core::WaveData loadWave(unsigned int waveIndex) const override;
    };

} // namespace tdg::core

#endif // AUTO_WAVE_SOURCE_HPP