#ifndef MORTAR_HPP
#define MORTAR_HPP

#include "tower.hpp"

class Mortar : public Tower
{
private:
    /* data */
public:
    Mortar(int x_, int y_);
    ~Mortar();
    std::string getTypeName() const override;
};

#endif // MORTAR_HPP
