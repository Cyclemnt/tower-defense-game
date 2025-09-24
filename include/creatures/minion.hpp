#ifndef MINION_HPP
#define MINION_HPP

#include "creature.hpp"

class Minion : public Creature
{
private:
    /* data */
public:
    Minion();
    ~Minion();
    std::string getTypeName() const override;
};

#endif // MINION_HPP
