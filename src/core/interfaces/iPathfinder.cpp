#include <limits>
#include "core/interfaces/iPathfinder.hpp"

namespace tdg::core {
    
    std::vector<const Tile*> IPathfinder::findPathToClosestGoal(const Tile* start, std::vector<Tile*> goals) {
        int bestLen = std::numeric_limits<int>::max();
        std::vector<const Tile*> bestPath;

        for (const Tile* goal : goals) {
            std::vector<const Tile*> path = findPath(start, goal);

            if (!path.empty() && path.size() < bestLen) {
                bestLen = path.size();
                bestPath = std::move(path);
            }
        }
        return bestPath;
    }

} // namespace tdg::core
