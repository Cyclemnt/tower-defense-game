#ifndef CREATURE_MANAGER_HPP
#define CREATURE_MANAGER_HPP

#include <optional>
#include "core/creatures/creature.hpp"
#include "core/factories/creatureFactory.hpp"

namespace tdg::core { class Events; class Map; class IPathfinder; class CoreStorage; class Player; };

namespace tdg::core {
    
    class CreatureManager {
    public:
        CreatureManager(Events& events, Map& map, IPathfinder& pathfider, CoreStorage& cores, Player& player);
        void renderVideo(IVideoRenderer& vidRenderer) const; // Draws every Creature

        void update(float dt, Events& events); // Main function to create new creatures and update them

        void spawn(Creature::Type type, unsigned int level, std::optional<unsigned int> entry); // Spawns a new creature
        void updatePaths(); // Computes new path for every creature

        bool isWaveOver() const noexcept { return m_creatures.empty(); }

        const std::vector<CreaturePtr>& creatures() const { return m_creatures; }

    private:
        void handleSpawnEvents(Events& events); // Spawns creature following spawn events
        void handlePathEvents(Events& events); // Request cores on coreStorage / free loot on death
        void handleDeadCreatures(Events& events); // Clears dead creatures from m_creatures

        CreatureFactory m_factory;

        Map& m_map;
        IPathfinder& m_pathfinder;
        CoreStorage& m_cores;
        Player& m_player;

        std::vector<CreaturePtr> m_creatures;
    };

} // namespace tdg::core

#endif // CREATURE_MANAGER_HPP