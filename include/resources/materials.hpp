#ifndef MATERIALS_HPP
#define MATERIALS_HPP

#include <array>

/**
 * @class Materials
 * @brief Tracks the player's building resources.
 *
 * The player has three types of materials, inspired by
 * the periodic table:
 * - Gold (Au)
 * - Silver (Ag)
 * - Copper (Cu)
 */
class Materials {
private:
    int au;     ///< Gold
    int ag;     ///< Silver
    int cu;     ///< Copper

public:
    Materials(int initialAu = 100, int initialAg = 100, int initialCu = 100);
    ~Materials();

    /// @return Current balance of resources {Au, Ag, Cu}.
    std::array<int, 3> getBalance() const;

    /// @brief Adds resources to the balance.
    void add(std::array<int, 3> amounts);

    /// @brief Spends resources from the balance.
    void spend(std::array<int, 3> amounts);
};

#endif // MATERIALS_HPP
