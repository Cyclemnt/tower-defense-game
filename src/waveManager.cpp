#include <cmath>
#include "../include/waveManager.hpp"
#include "../include/game.hpp"

WaveManager::WaveManager() {
    // Default weights for [Minion, Drone, Tank]
    spawnDist = std::discrete_distribution<int>({60, 30, 10});
}

void WaveManager::generateNextWave() {
    ++currentWave;
    pendingSpawns.clear();

    int baseCount = 5;
    int waveSize = baseCount + currentWave * currentWave * 0.01f;

    // Adjust probabilities as waves increase
    std::vector<float> weights = {
        std::max(5.0f, 60.0f - currentWave * 2.5f),  // Minion
        std::min(40.0f, 30.0f + currentWave * 1.5f), // Drone
        std::min(30.0f, 10.0f + currentWave)        // Tank
    };
    spawnDist = std::discrete_distribution<int>(weights.begin(), weights.end());

    for (int i = 0; i < waveSize; ++i) {
        int typeIdx = spawnDist(rng);
        pendingSpawns.push_back(static_cast<CreatureType>(typeIdx));
    }

    currentIndex = 0;
    timeSinceLastSpawn = 0.0f;
}

void WaveManager::update(float dt, Game& game) {
    if (pendingSpawns.empty()) {
        generateNextWave();
        return;
    }

    timeSinceLastSpawn += dt;

    if (currentIndex < pendingSpawns.size() && timeSinceLastSpawn >= spawnInterval) {
        game.spawnCreature(pendingSpawns[currentIndex]);
        ++currentIndex;
        timeSinceLastSpawn = 0.0f;
    }

    if (currentIndex >= pendingSpawns.size()) {
        // Small delay before next wave
        if (timeSinceLastSpawn > 3.0f) {
            generateNextWave();
        }
    }
}

int WaveManager::getCurrentWave() const { return currentWave; }
