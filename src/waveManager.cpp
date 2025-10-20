#include "../include/waveManager.hpp"
#include "../include/game.hpp"
#include <ctime>
#include <cstdlib>
#include <cmath>

WaveManager::WaveManager() {
    setMode(WaveMode::FromJson);
    loadLevelFromJson("../assets/waves/level1.json");
}

bool WaveManager::isWaveOver(const Game& game) const {
    return pendingWave.empty() && game.getCreatures().empty();
}

void WaveManager::generateNextWave() {
    if (currentWave >= maxWaves) return;

    ++currentWave;
    pendingWave.clear();
    waveFinished = false;

    int totalUnits = static_cast<int>(2 + std::pow(currentWave, waveSizeCoef));

    for (int i = 0; i < totalUnits; ++i) {
        CreatureType chosen = static_cast<CreatureType>(dist(gen));
        pendingWave.push_back({chosen, 1});
    }

    spawnInterval = 5.0f / std::max(totalUnits, 1);
    spawnTimer = 0.0f;
    pendingTypeIndex = 0;
    pendingUnitCount = !pendingWave.empty() ? pendingWave[0].count : 0;
    nextWaveCountdown = 3.0f;
}

void WaveManager::generateNextWaveFromJson() {
    if (jsonLoader && jsonLoader->hasNextWave()) {
        ++currentWave;
        pendingWave = toWaveManagerEntries(jsonLoader->getNextWave());
        pendingTypeIndex = 0;
        pendingUnitCount = !pendingWave.empty() ? pendingWave[0].count : 0;
        spawnTimer = 0.0f;
        waveFinished = false;

        int totalUnits = 0;
        for (const auto& e : pendingWave)
            totalUnits += e.count;
        spawnInterval = 5.0f / std::max(totalUnits, 1);
        nextWaveCountdown = 3.0f;
    }
}

void WaveManager::update(float dt, Game& game) {
    switch (mode) {
        case WaveMode::Automatic:
            updateAutomatic(dt, game);
            break;
        case WaveMode::FromJson:
            updateFromJson(dt, game);
            break;
    }
}

void WaveManager::updateAutomatic(float dt, Game& game) {
    if (currentWave >= maxWaves && pendingWave.empty() && game.getCreatures().empty())
        return;

    if (!waveFinished && isWaveOver(game)) {
        waveFinished = true;
        return;
    }

    if (waveFinished) {
        nextWaveCountdown -= dt;
        if (nextWaveCountdown <= 0.0f)
            generateNextWave();
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

void WaveManager::updateFromJson(float dt, Game& game) {
    if (!jsonLoader) return;

    if (!waveFinished && isWaveOver(game)) {
        waveFinished = true;
        return;
    }

    if (waveFinished) {
        nextWaveCountdown -= dt;
        if (nextWaveCountdown <= 0.0f) {
            if (jsonLoader->hasNextWave())
                generateNextWaveFromJson();
        }
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

void WaveManager::loadLevelFromJson(const std::string& filename) {
    jsonLoader = std::make_unique<JsonWaveLoader>(filename);
}

int WaveManager::getCurrentWave() const { return currentWave; }
void WaveManager::setMaxWaves(int max) { maxWaves = max; }

void WaveManager::setMode(WaveMode newMode) { mode = newMode; }
WaveMode WaveManager::getMode() const { return mode; }

std::vector<WaveManager::WaveEntry> toWaveManagerEntries(
    const std::vector<JsonWaveLoader::WaveEntry>& entries)
{
    std::vector<WaveManager::WaveEntry> result;
    result.reserve(entries.size());
    for (const auto& e : entries)
        result.push_back({ e.type, e.count });
    return result;
}
