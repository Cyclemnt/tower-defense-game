#ifndef MINION_HPP
#define MINION_HPP

#include <string>
#include "creature.hpp"

/**
 * @class Minion
 * @brief Light and fast enemy type.
 *
 * A Minion has low health but higher speed compared to other creatures.
 * Typically used to overwhelm defenses by sheer numbers.
 */
class Minion : public Creature {
public:
    Minion();
    ~Minion();

    /// @return The type name of this creature ("Minion").
    std::string getTextureName(int frame) const override;
};

#endif // MINION_HPP
