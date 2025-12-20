#ifndef I_PATHFINDER_HPP
#define I_PATHFINDER_HPP

#include <vector>

namespace tdg::core { struct Tile; }

namespace tdg::core {

    /// @brief Abstract pathfinder used by domain logic to compute navigation.
    class IPathfinder {
    public:
        virtual ~IPathfinder() = default;

        /// @brief Computes a path between two tiles using A*.
        /// @return A list of tiles forming the path from start to goal, or empty if none.
        virtual std::vector<const Tile*> findPath(const Tile* start, const Tile* goal, bool ignoreTowers = false) const = 0;

        /// @brief Computes and chooses shortest path between multiple goals
        std::vector<const Tile*> findPathToClosestGoal(const Tile* start, std::vector<Tile*> goals);
    };

} // namespace tdg::core

#endif // I_PATHFINDER_HPP