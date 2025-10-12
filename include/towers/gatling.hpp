#ifndef GATLING_HPP
#define GATLING_HPP

#include <string>
#include "tower.hpp"

/**
 * @class Gatling
 * @brief Rapid-fire tower type.
 *
 * Fires bullets quickly with low damage per shot,
 * effective against swarms of weak enemies.
 */
class Gatling : public Tower {
public:
    Gatling(int x_, int y_);
    ~Gatling();

    /// @return The type name of this tower ("Gatling").
    std::string getTypeName() const override;
};

#endif // GATLING_HPP
