#include "core/waveManager.hpp"

namespace tdg::core {

    explicit WaveManager::WaveManager(std::unique_ptr<IWaveSource> source)
        : m_source(std::move(source)) {}

    void WaveManager::update(float dt, Events events) {
        std::vector<SpawnEntry>& spawns = m_waves[m_waveIndex].spawns;

        if (m_spawnIndex < spawns.size())
            m_timer = std::max(m_timer - dt, 0.0f);
            m_timer -= dt;
        
        // Spawn creatures while timer <= 0
        while (m_spawnIndex < spawns.size() && m_timer <= 0.0f) {
            SpawnEntry& currentSpawn = spawns[m_spawnIndex];
            m_inWave = true;
            events.spawn.emplace(currentSpawn.enemyType, currentSpawn.spawnEntrance);
            ++m_spawnIndex;

            // Schedule next spawn if it exists
            if (m_spawnIndex < spawns.size())
                m_timer += currentSpawn.delay;
        }
    }

    void WaveManager::loadNext() {
        m_inWave = false;
        if (m_waveIndex < m_waves.size()) {
            m_spawnIndex = 0;
            ++m_waveIndex;
            m_timer = m_waves[m_waveIndex].startDelay + m_waves[m_waveIndex].spawns[0].delay;
        }
    }

    bool WaveManager::allWavesSpawned() const noexcept {
        return m_waveIndex >= m_waves.size() && m_spawnIndex >= m_waves.back().spawns.size();
    }

    size_t WaveManager::getWaveNumber() const noexcept {
        return m_waveIndex + m_inWave + (m_waveIndex >= m_waves.size() && !m_inWave);
    }

    size_t WaveManager::getWavesQuantity() const noexcept {
        return m_waves.size();
    }

    float WaveManager::getTimeBeforeNext() const noexcept {
        // bool inWave = (m_spawnIndex < m_waves[m_waveIndex].spawns.size()) && ((m_spawnIndex == 0) && m_timer <= m_waves[m_waveIndex].spawns[m_spawnIndex].delay);
        return m_inWave ? 0.0f : m_timer < 0 ? 0.0f : m_timer;
    }

} // namespace tdg::core