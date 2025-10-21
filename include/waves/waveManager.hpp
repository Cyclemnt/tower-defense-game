#ifndef WAVE_MANAGER_HPP
#define WAVE_MANAGER_HPP

#include <memory>
#include <vector>
#include "iWaveSource.hpp"

class Game;

/**
 * @brief Handles timing and progression of waves (independent of source).
 */
class WaveManager {
private:
    std::unique_ptr<IWaveSource> source;

    int currentWave = 0;
    float spawnTimer = 0.0f;
    float spawnInterval = 0.5f;
    bool waveFinished = true;
    float nextWaveCountdown = 0.0f;

    std::vector<WaveEntry> pendingWave;
    size_t currentIndex = 0;

    void startNextWave();
    bool isWaveOver(const Game& game) const;

public:
    explicit WaveManager(std::unique_ptr<IWaveSource> src);
    void update(float dt, Game& game);

    int getCurrentWave() const { return currentWave; }
    bool hasMoreWaves() const { return source->hasNextWave(); }
};

#endif // WAVE_MANAGER_HPP
