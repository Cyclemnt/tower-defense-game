#include "core/waveManager.hpp"
#include "core/events.hpp"

namespace tdg::core {

    WaveManager::WaveManager(std::shared_ptr<IWaveSource> source)
        : m_source(source) {}

    void WaveManager::update(float dt, Events& events) {
        if (m_spawnIndex < m_wave.size())
            m_timer = std::max(m_timer - dt, 0.0f);
            // m_timer -= dt;
        
        // Spawn creatures while timer <= 0
        while (m_spawnIndex < m_wave.size() && m_timer <= 0.0f) {
            SpawnEntry& currentSpawn = m_wave[m_spawnIndex];
            m_inWave = true;
            events.spawn.push({currentSpawn.enemyType, currentSpawn.level, currentSpawn.spawnEntrance});
            ++m_spawnIndex;

            // Schedule next spawn if it exists
            if (m_spawnIndex < m_wave.size())
                m_timer += currentSpawn.delay;
        }
    }

    void WaveManager::loadNext() {
        m_inWave = false;
        if (m_waveIndex < waveCount()) {
            m_spawnIndex = 0;
            ++m_waveIndex;
            WaveData data = m_source->loadWave(m_waveIndex);
            m_wave = data.spawns;
            m_timer = data.startDelay + m_wave[0].delay;
        }
    }

    unsigned int WaveManager::waveFinished() const noexcept {
        return m_spawnIndex >= m_wave.size();
    }

    bool WaveManager::allWavesSpawned() const noexcept {
        return m_waveIndex >= waveCount() && m_spawnIndex >= m_wave.size();
    }

    float WaveManager::timeBeforeNext() const noexcept {
        return m_inWave ? 0.0f : m_timer < 0 ? 0.0f : m_timer;
    }

} // namespace tdg::core