#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <array>
#include "resources/materials.hpp"
class Tower;

/**
 * @class Player
 * @brief Represents the human player and their available resources.
 *
 * The Player manages construction materials used to build towers
 * and collect loot from defeated enemies. It ensures that resource
 * constraints are respected during gameplay.
 */
class Player {
private:
    Materials balance; ///< Player’s available materials (Au, Ag, Cu).

public:
    /// @brief Constructs a new Player with an initial material balance.
    /// @param initialBalance Starting amount of materials (default: 100 each).
    explicit Player(Materials initialBalance = Materials({100u, 100u, 100u})) noexcept;

    /// @brief Default destructor.
    ~Player() = default;

    /// @brief Retrieves the current material balance.
    /// @return Constant reference to the internal materials quantities.
    [[nodiscard]] const Materials::Quantities& getBalance() const noexcept { return balance.getQuantities(); }

    /// @brief Checks whether the player can afford to build a specific tower.
    /// @param tower The tower whose cost should be compared to available materials.
    /// @return True if the player can afford it, false otherwise.
    [[nodiscard]] bool canAfford(const Tower& tower) const noexcept;

    /// @brief Deducts materials from the player to pay for a tower.
    /// @param tower The tower being purchased.
    /// @pre canAfford(tower) == true
    void buy(const Tower& tower) noexcept;

    /// @brief Adds materials to the player’s balance.
    /// Typically called when a creature is defeated and drops loot.
    /// @param loot The materials gained.
    void addMaterials(const Materials::Quantities& loot) noexcept;
};

#endif // PLAYER_HPP
