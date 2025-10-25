#include "../../include/waves/waveManager.hpp"
#include "../../include/game.hpp"
#include <iostream>

WaveManager::WaveManager(std::unique_ptr<IWaveSource> src)
    : source(std::move(src)) {}

void WaveManager::update(float dt, Game& game) {
    if (spawnIndex < activeWave.spawns.size()) timer -= dt;

    // Spawn creatures
    if (spawnIndex < activeWave.spawns.size() && timer <= 0.0f) {
        game.spawnCreature(activeWave.spawns[spawnIndex].type);
        ++spawnIndex;
        if (spawnIndex < activeWave.spawns.size()) timer += activeWave.spawns[spawnIndex].delay;
    }

    // When wave is done and no more creatures alive : prepare next
    if (spawnIndex >= activeWave.spawns.size() && game.getCreatures().empty()) {
        if (source->hasMoreWaves()) {
            activeWave = source->nextWave();
            timer = activeWave.delay + activeWave.spawns[0].delay;
            spawnIndex = 0;
            ++waveCount;
        }
    }
}
