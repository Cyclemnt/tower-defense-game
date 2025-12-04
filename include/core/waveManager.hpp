#ifndef WAVE_MANAGER_HPP
#define WAVE_MANAGER_HPP

#include <vector>
#include <memory>
#include <functional>
#include "interfaces/iWaveSource.hpp"
#include "core/events.hpp"

namespace tdg::core {

    class WaveManager {
    public:
        using SpawnCallback = std::function<void(const SpawnEntry&)>;

        explicit WaveManager(std::unique_ptr<IWaveSource> source);

        void update(float dt, Events events);

        void loadNext();

        int currentWaveIndex() const noexcept { return m_waveIndex; }
        bool allWavesSpawned() const noexcept;
        unsigned int getWaveNumber() const noexcept;
        unsigned int waveCount() const noexcept;
        float getTimeBeforeNext() const noexcept;

    private:
        std::unique_ptr<IWaveSource> m_source;
        std::vector<SpawnEntry> m_wave;
        float m_timer{0};
        size_t m_waveIndex{0};
        size_t m_spawnIndex{0};
        bool m_inWave{false};
    };

} // namespace tdg::core

#endif // WAVE_MANAGER_HPP