#ifndef WAVE_MANAGER_HPP
#define WAVE_MANAGER_HPP

#include "interfaces/iWaveSource.hpp"
#include <vector>
#include <chrono>
#include <memory>
#include <functional>

namespace tdg::core {

    class WaveManager {
    public:
        using SpawnCallback = std::function<void(const SpawnEntry&)>;

        explicit WaveManager(std::unique_ptr<IWaveSource> source);

        void update(std::chrono::milliseconds dt);

        int currentWaveIndex() const noexcept { return m_waveIndex; }
        bool allWavesCleared() const noexcept;
        bool WaveManager::isWaveComplete() const noexcept;
        size_t WaveManager::getWaveNumber() const noexcept;
        size_t WaveManager::getWavesQuantity() const noexcept;
        float WaveManager::getTimeBeforeNext() const noexcept;

    private:
        std::unique_ptr<IWaveSource> m_source;
        std::vector<WaveData> m_waves;
        std::chrono::milliseconds m_timer{0};
        size_t m_waveIndex{0};
        size_t m_spawnIndex{0};
        bool m_inWave{false};
    };

} // namespace tdg::core

#endif // WAVE_MANAGER_HPP