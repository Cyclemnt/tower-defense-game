#ifndef MAP_HPP
#define MAP_HPP

#include "../include/tiles/tile.hpp"
#include <array>

class Map {
private:
    // 2D map
    std::array<std::array<Tile, 16>, 16> map;
    // Map level
    int level;
    
public:
    Map(/* args */);
    ~Map();
};

#endif // MAP_HPP
