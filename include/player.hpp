#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "resources/materials.hpp"
#include "resources/cores.hpp"
#include "map/tile.hpp"
#include "towers/tower.hpp"

/**
 * @class Player
 * @brief Represents the player and their resources.
 *
 * The player can build towers if they have enough
 * materials. They must defend the cores from being stolen.
 */
class Player {
private:
    Materials materials;    ///< Building resources
    
public:
    Player();
    ~Player();
    
    const Materials& getMaterials() const;

    /// @brief Check if the player has enough resources for a tower.
    bool canAfford(const Tower& tower);

    /// @brief Deduct resources when building a tower.
    void pay(const Tower& tower);

    /// @brief Add materials to the player's balance.
    void addMaterials(std::array<int, 3> loot);
};

#endif // PLAYER_HPP
