#include <cmath>
#include <cstdlib>
#include <ctime>
#include "../include/waveManager.hpp"
#include "../include/game.hpp"

WaveManager::WaveManager()
    : currentWave(0), spawnTimer(0.0f), spawnInterval(0.5f),
      pendingTypeIndex(0), pendingUnitCount(0),
      maxWaves(10), timeSinceWaveEnd(0.0f), waveFinished(false) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

// ------------------------------------------------------------
// Generates a new wave of enemies based on wave number.
// Each wave increases in difficulty by total weight.
// ------------------------------------------------------------
void WaveManager::generateNextWave() {
    if (currentWave >= maxWaves) return; // Stop if max number of waves reached

    ++currentWave;
    pendingWave.clear();
    waveFinished = false;
    timeSinceWaveEnd = 0.0f;

    // Total weight increases with wave number
    int maxWeightThisWave = 5 + currentWave * 3;
    int remainingWeight = maxWeightThisWave;

    // Defines the "weight" cost of each creature type
    auto getCreatureWeight = [](CreatureType type) -> int {
        switch (type) {
            case CreatureType::Minion: return 1;
            case CreatureType::Drone:  return 2;
            case CreatureType::Tank:   return 3;
            default: return 1;
        }
    };

    // Randomly select creatures until total weight is exhausted
    while (remainingWeight > 0) {
        CreatureType chosen = types[std::rand() % static_cast<int>(types.size())];
        int weight = getCreatureWeight(chosen);

        if (weight <= remainingWeight) {
            pendingWave.push_back({chosen, 1});
            remainingWeight -= weight;
        } else {
            break;
        }
    }

    // Compute the spawn interval (spread over 5 seconds total)
    int totalUnits = 0;
    for (auto& entry : pendingWave) totalUnits += entry.count;
    spawnInterval = 5.0f / std::max(totalUnits, 1);

    spawnTimer = 0.0f;
    pendingTypeIndex = 0;
    pendingUnitCount = !pendingWave.empty() ? pendingWave[0].count : 0;

    // std::cout << "[WaveManager] New wave #" << currentWave
    //           << " (" << totalUnits << " enemies)" << std::endl;
}

// ------------------------------------------------------------
// Updates the current wave state over time.
// Handles spawning, delays, and transition between waves.
// ------------------------------------------------------------
void WaveManager::update(float dt, Game& game) {
    // If all waves have been launched and no creatures remain, stop updating
    if (currentWave >= maxWaves && pendingWave.empty() && game.getCreatures().empty())
        return;

    // Detect when a wave has ended (no pending spawns, no active creatures)
    if (pendingWave.empty() && game.getCreatures().empty() && !waveFinished) {
        waveFinished = true;
        timeSinceWaveEnd = 0.0f;
        // std::cout << "[WaveManager] Wave #" << currentWave << " finished!" << std::endl;
        return;
    }

    // Wait a few seconds before generating the next wave
    if (waveFinished) {
        timeSinceWaveEnd += dt;
        if (timeSinceWaveEnd >= 3.0f) { // 3-second delay between waves
            generateNextWave();
        }
        return;
    }

    // If no wave is currently active, skip
    if (pendingWave.empty()) return;

    // Spawn enemies progressively during the wave
    spawnTimer += dt;
    if (spawnTimer >= spawnInterval && pendingTypeIndex < (int)pendingWave.size()) {
        spawnTimer = 0.0f;
        const auto& entry = pendingWave[pendingTypeIndex];
        game.spawnCreature(entry.type);

        // Move to next enemy or type
        if (--pendingUnitCount <= 0) {
            ++pendingTypeIndex;
            if (pendingTypeIndex < (int)pendingWave.size())
                pendingUnitCount = pendingWave[pendingTypeIndex].count;
            else
                pendingWave.clear(); // Entire wave has been spawned
        }
    }
}

// ------------------------------------------------------------
// Returns the index of the current wave.
// ------------------------------------------------------------
int WaveManager::getCurrentWave() const {
    return currentWave;
}

// ------------------------------------------------------------
// Sets the maximum number of waves allowed.
// ------------------------------------------------------------
void WaveManager::setMaxWaves(int max) {
    maxWaves = max;
}
