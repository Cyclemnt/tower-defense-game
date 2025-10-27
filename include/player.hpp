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
    Materials balance; ///< Building resources
    
public:
    Player(Materials balance_ = Materials({100u, 100u, 100u}));
    ~Player();
    
    const Materials::Quantities& getBalance() const { return balance.getQuantities(); }

    /// @brief Check if the player has enough resources for a tower.
    bool canAfford(const Tower& tower);

    /// @brief Deduct resources when building a tower.
    void buy(const Tower& tower);

    /// @brief Add materials to the player's balance.
    void addMaterials(const Materials::Quantities& loot);
};

#endif // PLAYER_HPP
