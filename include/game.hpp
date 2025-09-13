#ifndef GAME_HPP
#define GAME_HPP

#include "map/map.hpp"
#include "towers/tower.hpp"
#include "creatures/creature.hpp"
#include "player.hpp"
#include <vector>

class Game {
private:
    // Map
    Map map;

    // Current towers
    std::vector<Tower*> towers;
    
    // Current creatures
    std::vector<Creature*> creatures;
    
    // Player
    Player player;

    // Elapsed time since game start
    double elapsedTime;
    
public:
    Game(/* args */);
    ~Game();
    
    void run();
    void update();
    void render();
    void spawnWave();
};

#endif // GAME_HPP
