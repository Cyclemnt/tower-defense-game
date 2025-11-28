#ifndef I_PATHFINDER_HPP
#define I_PATHFINDER_HPP

#include "core/map.hpp"
#include <vector>

namespace tdg::core {

    /// @brief Abstract pathfinder used by domain logic to compute navigation.
    class IPathfinder {
    public:
        virtual ~IPathfinder() = default;

        /// Compute path from (sx,sy) to (dx,dy). Returns optional vector of
        /// PathPoint if path exists.
        virtual std::vector<const Tile*> findPath(const Tile* start, const Tile* goal, bool ignoreTowers = false) const = 0;
    };

} // namespace tdg::core

#endif // I_PATHFINDER_HPP