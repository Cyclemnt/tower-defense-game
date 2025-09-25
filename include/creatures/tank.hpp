#ifndef TANK_HPP
#define TANK_HPP

#include "creature.hpp"

class Tank : public Creature
{
private:
    /* data */
public:
    Tank();
    ~Tank();
    std::string getTypeName() const override;
};

#endif // TANK_HPP
