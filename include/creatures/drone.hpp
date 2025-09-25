#ifndef DRONE_HPP
#define DRONE_HPP

#include "creature.hpp"

class Drone : public Creature
{
private:
    /* data */
public:
    Drone();
    ~Drone();
    std::string getTypeName() const override;
};

#endif // DRONE_HPP
