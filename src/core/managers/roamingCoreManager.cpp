#include <cmath>
#include "core/managers/roamingCoreManager.hpp"

#include "core/events.hpp"
#include "core/map.hpp"
#include "core/interfaces/iPathfinder.hpp"
#include "core/coreStorage.hpp"

namespace tdg::core {

    RoamingCoreManager::RoamingCoreManager(Map& map, IPathfinder& pathfider, CoreStorage& cores)
        : m_map(map), m_pathfinder(pathfider), m_cores(cores) {}

    void RoamingCoreManager::update(float dt, Events& events) {
        handleDroppedCores(events);
        for (RoamingCore& roamingCore : m_roamingCores) roamingCore.update(dt, events);
        handleArrivedRoamingCores();
    }

    void RoamingCoreManager::handleDroppedCores(Events& events) {
        while (!events.droppedCores.empty()) {
            Events::DroppedCores event = events.droppedCores.front();

            Tile* start = m_map.tileAt(std::round(event.x), std::round(event.y));
            std::vector<const Tile*> path = m_pathfinder.findPath(start, m_map.corePoint());

            m_roamingCores.emplace_back(event.dropped, event.x, event.y, path);

            events.droppedCores.pop();
        }
    }

        void RoamingCoreManager::handleArrivedRoamingCores() {
        for (auto it = m_roamingCores.begin(); it != m_roamingCores.end();) {
            RoamingCore& roamingCore = *it;

            if (!roamingCore.isRoaming()) {
                m_cores.returnCores(roamingCore.groupQuantity());
                // Erease the roaming core
                it = m_roamingCores.erase(it);
            }
            else { ++it; }
        }
    }
    
} // namespace tdg::core
