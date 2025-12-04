#ifndef I_PATHFINDER_HPP
#define I_PATHFINDER_HPP

#include <vector>
#include "core/map.hpp"

namespace tdg::core {

    /// @brief Abstract pathfinder used by domain logic to compute navigation.
    class IPathfinder {
    public:
        virtual ~IPathfinder() = default;

        /// @brief Computes path from (sx,sy) to (dx,dy). Returns optional vector of
        /// @return PathPoint if path exists.
        virtual std::vector<const Tile*> findPath(const Tile* start, const Tile* goal, bool ignoreTowers = false) const = 0;

        std::vector<const Tile*> findPathToClosestGoal(const Tile* start, std::vector<Tile*> goals);
    };

} // namespace tdg::core

#endif // I_PATHFINDER_HPP