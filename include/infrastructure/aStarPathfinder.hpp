#ifndef A_STAR_PATHFINDER_HPP
#define A_STAR_PATHFINDER_HPP

#include "core/interfaces/iPathfinder.hpp"
#include "core/map.hpp"

namespace tdg::core {

    class AStarPathfinder : public IPathfinder {
    public:
        /// @brief Constructs a Pathfinder operating on the given map.
        explicit AStarPathfinder(const core::Map& map) noexcept;

        /// @brief Computes a path between two tiles using A*.
        /// @return A list of tiles forming the path from start to goal, or empty if none.
        std::vector<PathPoint> findPath(const Tile* start, const Tile* goal, bool ignoreTowers = false) const override;
    
    private:
        const core::Map& m_map;

        /// @brief Represents a node in the A* search process.
        struct Node {
            const Tile* tile;  ///< Tile corresponding to this node.
            int gCost;         ///< Cost from start to this node.
            int hCost;         ///< Heuristic cost to goal.
            Node* parent;      ///< Parent node for path reconstruction.
            constexpr int fCost() const noexcept { return gCost + hCost; }
        };

        /// @brief Heuristic cost estimation between two tiles (Manhattan distance).
        int heuristic(const core::Tile* a, const core::Tile* b) const noexcept;
    };

} // namespace tdg::core

#endif // A_STAR_PATHFINDER_HPP