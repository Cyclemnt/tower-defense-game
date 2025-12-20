#ifndef WAVE_MANAGER_HPP
#define WAVE_MANAGER_HPP

#include <vector>
#include <memory>
#include "interfaces/iWaveSource.hpp"

namespace tdg::core { class Events; }

namespace tdg::core {

    class WaveManager {
    public:
        explicit WaveManager(std::shared_ptr<IWaveSource> source);

        void update(float dt, Events& events); // Main function to read m_wave and create spawn events

        void loadNext(); // Asks m_source for the next wave

        unsigned int waveIndex() const noexcept { return m_waveIndex; }
        unsigned int waveCount() const noexcept { return m_source->waveCount(); }
        unsigned int waveFinished() const noexcept; // Returns true if the whole wave has been spawned
        bool allWavesSpawned() const noexcept; // Returns true if every wave has been spawned
        float timeBeforeNext() const noexcept; // Returns the timer if currently in a wave

    private:
        std::shared_ptr<IWaveSource> m_source; // Source of the waves data
        std::vector<SpawnEntry> m_wave; // Actual wave

        size_t m_waveIndex{0};
        size_t m_spawnIndex{0};
        
        float m_timer{0};
        bool m_inWave{false};
    };

} // namespace tdg::core

#endif // WAVE_MANAGER_HPP