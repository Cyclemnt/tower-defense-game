#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "resources/materials.hpp"
#include "resources/cores.hpp"
#include "map/tile.hpp"
#include "towers/tower.hpp"

class Player {
private:
    // Ressources
    Materials materials;
    Cores cores;
    
public:
    Player(/* args */);
    ~Player();
    
    void placeTower(Tile* tile, Tower* tower);
    void upgradeTower(Tower* tower);
    bool canAfford(const Tower& tower);
    void pay(const Tower& tower);
};

#endif // PLAYER_HPP
