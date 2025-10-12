#ifndef TANK_HPP
#define TANK_HPP

#include <string>
#include "creature.hpp"

/**
 * @class Tank
 * @brief Heavy enemy type.
 *
 * A Tank has very high health and shield but moves slowly.
 * It is designed to absorb large amounts of damage while
 * escorting other weaker enemies.
 */
class Tank : public Creature {
public:
    Tank();
    ~Tank();

    /// @return The type name of this creature ("Tank").
    std::string getTypeName() const override;
};

#endif // TANK_HPP
