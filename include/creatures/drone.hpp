#ifndef DRONE_HPP
#define DRONE_HPP

#include <string>
#include "creature.hpp"

/**
 * @class Drone
 * @brief Standard enemy type.
 *
 * A Drone represents the baseline enemy: average health, speed and
 * no special abilities. Used as the most common wave unit.
 */
class Drone : public Creature {
private:
    bool boost;
public:
    Drone(bool boost_= false);
    ~Drone();

    /// @return The type name of this creature ("Drone").
    std::string getTextureName(int frame) const override;
};

#endif // DRONE_HPP
