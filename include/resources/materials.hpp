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
    std::array<unsigned int, 3> materials;

public:
    Materials(std::array<unsigned int, 3> materials_ = {100u, 100u, 100u});
    ~Materials();

    /// @return Current balance of resources {Au, Ag, Cu}.
    std::array<unsigned int, 3> getBalance() const;

    /// @brief Adds resources to the balance.
    void add(std::array<unsigned int, 3> amounts);

    /// @brief Spends resources from the balance.
    void spend(std::array<unsigned int, 3> amounts);
};

#endif // MATERIALS_HPP
