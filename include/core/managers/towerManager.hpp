#ifndef TOWER_MANAGER_HPP
#define TOWER_MANAGER_HPP

#include <optional>
#include "core/towers/tower.hpp"
#include "core/factories/towerFactory.hpp"

namespace tdg::core { class Events; class Map; class Player; };

namespace tdg::core {
    
    class TowerManager {
    public:
        TowerManager(Events& events, Map& map, Player& player, const std::vector<CreaturePtr>& creatures);
        void renderVideo(IVideoRenderer& vidRenderer) const; // Draws every Creature

        void update(float dt, Events& events); // Main function to create new creatures and update them
        
        bool buildTower(Tower::Type type, int x, int y); // Builds a tower
        bool upgradeTower(int x, int y); // Upgrades a tower
        bool sellTower(int x, int y); // Sells a tower

        std::optional<float> towerRangeAt(int x, int y) const; // Gives the (x, y) tower's range if it exists

    private:
        // TowerPtr create(Tower::Type type, int x, int y) const; // Factory
        TowerFactory m_factory;
        
        Map& m_map;
        Player& m_player;

        Events& m_events;
        std::vector<TowerPtr> m_towers;
        const std::vector<CreaturePtr>& m_creatures;
    };

} // namespace tdg::core

#endif // TOWER_MANAGER_HPP