#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include "map/map.hpp"
#include <array>
#include <vector>

class Pathfinder {
private:
    // Access to the map
    Map* map;
    
public:
    Pathfinder(/* args */);
    ~Pathfinder();

    void findShortestPath() const;
};

#endif // PATHFINDER_HPP
