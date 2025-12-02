#include <cmath>
#include "core/interfaces/iPathfinder.hpp"

namespace tdg::core {
    
    std::vector<const Tile*> IPathfinder::findPathToClosestGoal(const Tile* start, std::vector<Tile*> goals) {
        int bestLen = std::numeric_limits<int>::max();
        std::vector<const Tile*> bestPath;

        for (const auto& goal : goals) {
            std::vector<const Tile*> path = findPath(start, goal);

            if (!path.empty() && path.size() < bestLen) {
                bestLen = path.size();
                bestPath = std::move(path);
            }
        }
    }

} // namespace tdg::core
