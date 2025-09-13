#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "../map/tile.hpp"
#include <vector>

class Creature {
private:
    // Specifications of the creature
    int health;
    int shield;
    int speed;

    // Amount of cores currently on the creature
    int carriedCores;

    // Path to follow
    std::vector<Tile*> path;
    
public:
    Creature(/* args */);
    ~Creature();
    
    void move();
    void takeDamage(int amount);
    void stealCore();
    void exitMap();
};

#endif // CREATURE_HPP
