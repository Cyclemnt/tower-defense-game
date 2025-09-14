#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include "map/map.hpp"
#include <vector>

class Pathfinder {
private:
    // Access to the map
    const Map& map;

    // Node structure
    struct Node {
        Tile* tile;
        int gCost; // cost from start
        int hCost; // heuristic to goal
        Node* parent;

        int fCost() const { return gCost + hCost; }
    };

    // Heuristic (can be changed if needed)
    int heuristic(Tile* a, Tile* b) const;
    
public:
    Pathfinder(const Map& m);
    ~Pathfinder();

    // Find path from start tile to goal tile (using A* algorithm)
    std::vector<Tile*> findPath(Tile* start, Tile* goal) const;
};

#endif // PATHFINDER_HPP
