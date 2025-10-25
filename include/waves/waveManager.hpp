#ifndef WAVE_MANAGER_HPP
#define WAVE_MANAGER_HPP

#include <memory>
#include "iWaveSource.hpp"

class Game;

class WaveManager {
private:
    std::unique_ptr<IWaveSource> source;
    WaveData activeWave;
    size_t spawnIndex = 0;
    float timer = 0.0f;
    int waveCount = 0;

public:
    explicit WaveManager(std::unique_ptr<IWaveSource> src);
    void update(float dt, Game& game);
    int getCurrentWave() const { return waveCount; }
};

#endif // WAVE_MANAGER_HPP
