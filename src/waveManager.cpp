#include <random>
#include <ctime>
#include <cstdlib>
#include "../include/waveManager.hpp"
#include "../include/game.hpp"

WaveManager::WaveManager()
    : currentWave(0), spawnTimer(0.0f), spawnInterval(0.5f),
      pendingTypeIndex(0), pendingUnitCount(0),
      maxWaves(10), waveFinished(false), timeSinceWaveEnd(0.0f) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

bool WaveManager::isWaveOver(const Game& game) const {
    return pendingWave.empty() && game.getCreatures().empty();
}

void WaveManager::generateNextWave() {
    if (currentWave >= maxWaves) return;

    ++currentWave;
    pendingWave.clear();
    waveFinished = false;

    // Number of units in the wave
    int totalUnits = static_cast<int>(2 + std::pow(currentWave, waveSizeCoef));

    // Minion ~50%, Drone ~33%, Tank ~17%
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<int> dist({50, 33, 17});

    for (int i = 0; i < totalUnits; ++i) {
        CreatureType chosen = static_cast<CreatureType>(dist(gen));
        pendingWave.push_back({chosen, 1});
    }

    spawnInterval = 5.0f / std::max(totalUnits, 1);
    spawnTimer = 0.0f;
    pendingTypeIndex = 0;
    pendingUnitCount = !pendingWave.empty() ? pendingWave[0].count : 0;
    timeSinceWaveEnd = 3.0f; // countdown before next wave
}

void WaveManager::update(float dt, Game& game) {
    if (currentWave >= maxWaves && pendingWave.empty() && game.getCreatures().empty())
        return;

    if (!waveFinished && isWaveOver(game)) {
        waveFinished = true;
        return;
    }

    if (waveFinished) {
        timeSinceWaveEnd -= dt;
        if (timeSinceWaveEnd <= 0.0f) generateNextWave();
        return;
    }

    spawnTimer += dt;
    while (!pendingWave.empty() && spawnTimer >= spawnInterval) {
        spawnTimer -= spawnInterval;

        WaveEntry& entry = pendingWave[pendingTypeIndex];
        game.spawnCreature(entry.type);

        entry.count--;
        if (entry.count <= 0) {
            ++pendingTypeIndex;
            if (pendingTypeIndex >= pendingWave.size()) pendingWave.clear();
        }
    }
}

int WaveManager::getCurrentWave() const { return currentWave; }
void WaveManager::setMaxWaves(int max) { maxWaves = max; }
