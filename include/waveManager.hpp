#ifndef WAVE_MANAGER_HPP
#define WAVE_MANAGER_HPP

#include <random>
#include <vector>
#include <memory>
#include "creatures/creature.hpp"
#include "jsonWaveLoader.hpp"

class Game;

enum class WaveMode {
    Automatic,
    FromJson
};

/**
 * @brief Handles the creation, timing, and progression of enemy waves.
 */
class WaveManager {
private:
    std::unique_ptr<JsonWaveLoader> jsonLoader;
    std::mt19937 gen{std::random_device{}()};
    std::discrete_distribution<int> dist{50, 33, 17};

    WaveMode mode = WaveMode::Automatic;

    int currentWave = 0;
    float spawnTimer = 0.0f;
    float spawnInterval = 0.5f;

    int pendingTypeIndex = 0;
    int pendingUnitCount = 0;

    float waveSizeCoef = 1.3f;
    int maxWaves = 10;
    bool waveFinished = false;
    float nextWaveCountdown = 0.0f;

public:
    struct WaveEntry {
        CreatureType type;
        int count;
    };

    std::vector<WaveEntry> pendingWave;

    WaveManager();

    void generateNextWave();                ///< Generate next wave of enemies automatically
    void generateNextWaveFromJson();        ///< Generate next wave from JSON

    void update(float dt, Game& game);      ///< Main update function — delegates based on mode
    void updateAutomatic(float dt, Game& game); ///< Handles automatic waves
    void updateFromJson(float dt, Game& game);  ///< Handles JSON-defined waves

    void loadLevelFromJson(const std::string& filename);
    int getCurrentWave() const;
    void setMaxWaves(int max);
    bool isWaveOver(const Game& game) const;

    void setMode(WaveMode newMode);
    WaveMode getMode() const;
};

std::vector<WaveManager::WaveEntry> toWaveManagerEntries(
    const std::vector<class JsonWaveLoader::WaveEntry>& entries);

#endif // WAVE_MANAGER_HPP
