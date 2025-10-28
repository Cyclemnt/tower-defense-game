#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include <vector>
#include <memory>
#include "map/map.hpp"
class Tile;

/**
 * @class Pathfinder
 * @brief A utility class that computes paths using the A* algorithm.
 *
 * The Pathfinder calculates the optimal route between two tiles on a map.
 * It supports optional tower-ignoring mode, allowing pathfinding even when
 * buildable tiles are occupied.
 */
class Pathfinder {
private:
    const Map& map; ///< Reference to the map used for pathfinding.

    /// @brief Represents a node in the A* search process.
    struct Node {
        const Tile* tile;  ///< Tile corresponding to this node.
        int gCost;         ///< Cost from start to this node.
        int hCost;         ///< Heuristic cost to goal.
        Node* parent;      ///< Parent node for path reconstruction.

        [[nodiscard]] constexpr int fCost() const noexcept { return gCost + hCost; }
    };

    /// @brief Heuristic cost estimation between two tiles (Manhattan distance).
    [[nodiscard]] int heuristic(const Tile* a, const Tile* b) const noexcept;

public:
    /// @brief Constructs a Pathfinder operating on the given map.
    explicit Pathfinder(const Map& m) noexcept;

    /// @brief Computes a path between two tiles using A*.
    /// @param start Starting tile.
    /// @param goal Destination tile.
    /// @param ignoreTowers If true, buildable tiles are considered walkable.
    /// @return A list of tiles forming the path from start to goal, or empty if none.
    [[nodiscard]] std::vector<const Tile*> findPath(const Tile* start, const Tile* goal, bool ignoreTowers = false) const;
};

#endif // PATHFINDER_HPP
