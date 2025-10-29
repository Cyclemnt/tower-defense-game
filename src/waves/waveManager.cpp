#include "../../include/waves/waveManager.hpp"
#include "../../include/game.hpp"

WaveManager::WaveManager(std::unique_ptr<IWaveSource> src) noexcept
    : source(std::move(src)) {}

void WaveManager::update(float dt, Game& game) {
    if (spawnIndex < activeWave.spawns.size())
        timer -= dt;

    // Spawn creatures when timer reaches 0
    if (spawnIndex < activeWave.spawns.size() && timer <= 0.0f) {
        inWave = true;
        game.spawnCreature(activeWave.spawns[spawnIndex].type);
        ++spawnIndex;

        // Schedule next spawn
        if (spawnIndex < activeWave.spawns.size())
            timer += activeWave.spawns[spawnIndex].delay;
    }

    // When wave is complete and all creatures are gone
    if (spawnIndex >= activeWave.spawns.size() && game.getCreatures().empty()) {
        inWave = false;
        if (source->hasMoreWaves()) {
            activeWave = source->nextWave();
            timer = activeWave.delay + activeWave.spawns[0].delay;
            spawnIndex = 0;
        }
    }
}

size_t WaveManager::getWaveNumber() const noexcept {
    return source->getWaveIndex() + inWave + !source->hasMoreWaves();
}

size_t WaveManager::getWavesQuantity() const noexcept {
    return source->getWavesQuantity();
}

float WaveManager::getTimeBeforeNext() const noexcept {
    return inWave ? 0.0f : timer < 0 ? 0.0f : timer;
}