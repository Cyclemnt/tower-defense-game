#ifndef MATERIALS_HPP
#define MATERIALS_HPP

#include <stdexcept>
#include <algorithm>

/**
 * @class Materials
 * @brief Manages the player's material resources.
 *
 * The player owns three elemental resources used for tower construction:
 * - **Gold (Au)**
 * - **Silver (Ag)**
 * - **Copper (Cu)**
 */
class Materials {
public:
    /// @brief Represents a fixed set of material amounts.
    struct Quantities {
        unsigned int au = 0; ///< Amount of gold.
        unsigned int ag = 0; ///< Amount of silver.
        unsigned int cu = 0; ///< Amount of copper.

        // --- Operators ---

        Quantities& operator+=(const Quantities& other) {
            au += other.au; ag += other.ag; cu += other.cu;
            return *this;
        }

        Quantities& operator-=(const Quantities& other) {
            au -= other.au; ag -= other.ag; cu -= other.cu;
            return *this;
        }
        
        Quantities& operator*(const float value) {
            au *= value; ag *= value; cu *= value;
            return *this;
        }

        Quantities& operator=(const int other) {
            au = other; ag = other; cu = other;
            return *this;
        }
    };

    
private:
    Quantities quantities; ///< Current material stock.

public:
    /// @brief Constructs a new Materials tracker.
    /// @param initial Initial material amounts.
    explicit Materials(Quantities initial = {100, 100, 100}) noexcept;

    /// @brief Default destructor.
    ~Materials() = default;

    // --- Getters ---
    [[nodiscard]] const Quantities& getQuantities() const noexcept { return quantities; }

    // --- Modification methods ---    
    /// @brief Adds new materials to the balance.
    /// @param other The materials to add.
    void add(const Quantities& other) noexcept { quantities += other; }

    /// @brief Spends materials if sufficient balance is available.
    /// @param cost The amount of materials to spend.
    /// @throws std::runtime_error if attempting to spend more than available.
    /// @param other 
    void spend(const Quantities& cost);

    /// @brief Checks whether the player can afford a given cost.
    /// @param cost The required materials.
    /// @return True if the player has enough of all resources.
    [[nodiscard]] bool canAfford(const Quantities& cost) const noexcept;
};

#endif // MATERIALS_HPP
