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
        void setSpawnCallback(SpawnCallback cb);

        int currentWaveIndex() const noexcept;
        bool allWavesCleared() const noexcept;

    private:
        std::unique_ptr<IWaveSource> m_source;
        std::vector<WaveData> m_waves;
        std::chrono::milliseconds m_time{0};
        size_t m_waveIndex{0};
        size_t m_nextSpawnIndex{0};
        SpawnCallback m_spawnCb;
    };

} // namespace tdg::core

#endif // WAVE_MANAGER_HPP