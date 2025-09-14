#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include "map/map.hpp"
#include <vector>

/// @brief A pathfinding utility that calculates the best path from a start tile to a goal tile using the A* algorithm.
class Pathfinder {
private:
    const Map& map; ///< Reference to the map used for pathfinding.

    /// @brief A struct representing a node in the pathfinding algorithm.
    struct Node {
        Tile* tile; ///< The tile represented by this node.
        int gCost; ///< The cost from the start tile to this node.
        int hCost; ///< The heuristic cost from this node to the goal.
        Node* parent; ///< The parent node, used for path reconstruction.

        /// @brief Calculates the total cost (g + h).
        /// @return The total cost of this node.
        int fCost() const { return gCost + hCost; }
    };

    /// @brief Heuristic function to estimate the cost from a given tile to the goal tile.
    /// @param a The starting tile.
    /// @param b The goal tile.
    /// @return The heuristic cost between the two tiles.
    int heuristic(Tile* a, Tile* b) const;

public:
    /// @brief Constructs a Pathfinder using the provided map.
    /// @param m The map to perform pathfinding on.
    Pathfinder(const Map& m);

    /// @brief Destroys the Pathfinder object.
    ~Pathfinder();

    /// @brief Finds the shortest path between a start tile and a goal tile using the A* algorithm.
    /// @param start The start tile.
    /// @param goal The goal tile.
    /// @return A vector of tiles representing the path from start to goal.
    std::vector<Tile*> findPath(Tile* start, Tile* goal) const;
};

#endif // PATHFINDER_HPP
