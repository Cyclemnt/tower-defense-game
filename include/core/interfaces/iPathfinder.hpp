#ifndef I_PATHFINDER_HPP
#define I_PATHFINDER_HPP

#include <vector>

namespace tdg::core {

    struct PathPoint { int x, y; };

    /// @brief Abstract pathfinder used by domain logic to compute navigation.
    class IPathfinder {
    public:
        virtual ~IPathfinder() = default;

        /// Compute path from (sx,sy) to (dx,dy). Returns optional vector of
        /// PathPoint if path exists.
        virtual std::vector<PathPoint> findPath(const Tile* start, const Tile* goal, bool ignoreTowers) const = 0;
    };

} // namespace tdg::core

#endif // I_PATHFINDER_HPP