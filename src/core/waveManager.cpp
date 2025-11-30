#include "core/waveManager.hpp"

namespace tdg::core {

    explicit WaveManager::WaveManager(std::unique_ptr<IWaveSource> source)
        : m_source(std::move(source)) {}

    void WaveManager::update(float dt) {
        if (m_spawnIndex < m_waves[m_waveIndex].spawns.size())
            m_timer -= dt;
        
        // Spawn creatures when timer reaches 0
        if (m_spawnIndex < m_waves[m_waveIndex].spawns.size() && m_timer <= 0.0f) {
            m_inWave = true;
            // game.spawnCreature(m_waves[m_waveIndex].spawns[m_spawnIndex].enemyType);
            ++m_spawnIndex;

            // Schedule next spawn
            if (m_spawnIndex < m_waves[m_waveIndex].spawns.size())
                m_timer += m_waves[m_waveIndex].spawns[m_spawnIndex].delay;
        }

        // When wave is complete and all creatures are gone
        if (isWaveComplete()) {
            m_inWave = false;
            if (/*m_source->hasMoreWaves()*/) {
                m_spawnIndex = 0;
                m_timer = m_waves[m_waveIndex].startDelay + m_waves[m_waveIndex].spawns[0].delay;
            }
        }
    }

    bool WaveManager::allWavesCleared() const noexcept {
        return isWaveComplete() && (m_waveIndex >= m_waves.size());
    }

    bool WaveManager::isWaveComplete() const noexcept {
        // return m_spawnIndex >= m_waves[m_waveIndex].spawns.size() && game.getCreatures().empty();
    }

    size_t WaveManager::getWaveNumber() const noexcept {
        // return m_waveIndex + m_inWave + (!source->hasMoreWaves() && !m_inWave);
    }

    size_t WaveManager::getWavesQuantity() const noexcept {
        return m_waves.size();
    }

    float WaveManager::getTimeBeforeNext() const noexcept {
        return m_inWave ? 0.0f : m_timer < 0 ? 0.0f : m_timer;
    }

} // namespace tdg::core