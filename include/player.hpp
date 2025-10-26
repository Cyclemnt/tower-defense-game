#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <array>
#include "resources/materials.hpp"
class Tower;

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
    Materials& getMaterials();

    /// @brief Check if the player has enough resources for a tower.
    bool canAfford(const Tower& tower);

    /// @brief Deduct resources when building a tower.
    void pay(const Tower& tower);

    /// @brief Add materials to the player's balance.
    void addMaterials(std::array<unsigned int, 3> loot);
};

#endif // PLAYER_HPP
