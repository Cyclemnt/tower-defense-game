#ifndef I_PATHFINDER_HPP
#define I_PATHFINDER_HPP

#include <vector>
#include <optional>

namespace tdg::core {

    struct PathPoint { int x; int y; };

    /// @brief Abstract pathfinder used by domain logic to compute navigation.
    class IPathfinder {
    public:
        virtual ~IPathfinder() = default;

        /// Compute path from (sx,sy) to (dx,dy). Returns optional vector of
        /// PathPoint if path exists.
        virtual std::optional<std::vector<PathPoint>> findPath(int sx, int sy, int dx, int dy) = 0;
    };

} // namespace tdg::core

#endif // I_PATHFINDER_HPP