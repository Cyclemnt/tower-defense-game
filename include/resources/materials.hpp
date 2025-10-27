#ifndef MATERIALS_HPP
#define MATERIALS_HPP

#include <array>
#include <stdexcept>

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
public:
    struct Quantities {
        unsigned int au = 0;
        unsigned int ag = 0;
        unsigned int cu = 0;

        Quantities& operator+=(const Quantities& other) {
            au += other.au;
            ag += other.ag;
            cu += other.cu;
            return *this;
        }

        Quantities& operator-=(const Quantities& other) {
            au -= other.au;
            ag -= other.ag;
            cu -= other.cu;
            return *this;
        }
        
        Quantities& operator*(const float value) {
            au *= value;
            ag *= value;
            cu *= value;
            return *this;
        }

        Quantities& operator=(const int other) {
            au = other;
            ag = other;
            cu = other;
            return *this;
        }
    };

    
private:
    Quantities quantities;

public:
    Materials(Quantities initial = {100, 100, 100});

    const Quantities& getQuantities() const;

    void add(const Quantities& other);

    void spend(const Quantities& other);

    bool canAfford(const Quantities& costs) const;
};

#endif // MATERIALS_HPP
