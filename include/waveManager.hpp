#ifndef WAVE_MANAGER_HPP
#define WAVE_MANAGER_HPP

#include <vector>
#include <random>
#include "creatures/creature.hpp"
class Game;

class WaveManager {
private:
    int currentWave = 0;
    // float timeSinceLastSpawn = 0.0f;
    // float spawnInterval = 1.0f;
    // int currentIndex = 0;

    // std::vector<CreatureType> pendingSpawns;

    // std::default_random_engine rng{std::random_device{}()};
    // std::discrete_distribution<int> spawnDist;

public:
    WaveManager();

    void update(float dt, Game& game);
    void generateNextWave();
    int getCurrentWave() const;
};

#endif // WAVE_MANAGER_HPP
