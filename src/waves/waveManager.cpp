#include "../../include/waves/waveManager.hpp"
#include "../../include/game.hpp"

WaveManager::WaveManager(std::unique_ptr<IWaveSource> src)
    : source(std::move(src)) {}

bool WaveManager::isWaveOver(const Game& game) const {
    return pendingWave.empty() && game.getCreatures().empty();
}

void WaveManager::startNextWave() {
    if (!source->hasNextWave()) return;
    pendingWave = source->nextWave();
    waveFinished = false;
    currentWave++;

    int totalUnits = 0;
    for (auto& e : pendingWave) totalUnits += e.count;

    spawnInterval = 5.0f / std::max(totalUnits, 1);
    spawnTimer = 0.0f;
    currentIndex = 0;
    nextWaveCountdown = 3.0f;
}

void WaveManager::update(float dt, Game& game) {
    if (waveFinished && source->hasNextWave()) {
        nextWaveCountdown -= dt;
        if (nextWaveCountdown <= 0.0f)
            startNextWave();
        return;
    }

    if (!waveFinished && isWaveOver(game)) {
        waveFinished = true;
        nextWaveCountdown = 3.0f;
        return;
    }

    if (pendingWave.empty()) return;

    spawnTimer += dt;
    while (spawnTimer >= spawnInterval && currentIndex < pendingWave.size()) {
        spawnTimer -= spawnInterval;

        auto& entry = pendingWave[currentIndex];
        game.spawnCreature(entry.type);
        if (--entry.count <= 0)
            currentIndex++;

        if (currentIndex >= pendingWave.size())
            pendingWave.clear();
    }
}
