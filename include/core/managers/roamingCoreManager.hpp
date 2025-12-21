#ifndef CORES_MANAGER_HPP
#define CORES_MANAGER_HPP

#include <vector>
#include "core/roamingCore.hpp"

namespace tdg::core { class Events; class Map; class IPathfinder; class CoreStorage; };

namespace tdg::core {

    class RoamingCoreManager {
    public:
        RoamingCoreManager(Map& map, IPathfinder& pathfider, CoreStorage& cores);

        void update(float dt, Events& events); // Main function to retrieve dropped cores and move roaming ones

        std::vector<RoamingCore>& roamingCores() noexcept { return m_roamingCores; }
        const std::vector<RoamingCore>& roamingCores() const noexcept { return m_roamingCores; }

    private:
        void handleDroppedCores(Events& events); // Converts dropped cores events to RoamingCores
        void handleArrivedRoamingCores(); // Clears dead roamin cores from m_roamingCores and deposit into m_cores

        Map& m_map;
        IPathfinder& m_pathfinder;
        CoreStorage& m_cores;

        std::vector<RoamingCore> m_roamingCores;
    };

} // namespace tdg::core

#endif // CORES_MANAGER_HPP