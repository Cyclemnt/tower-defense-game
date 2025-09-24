#ifndef LASER_HPP
#define LASER_HPP

#include "tower.hpp"

class Laser : public Tower
{
private:
    /* data */
public:
    Laser(int x_, int y_);
    ~Laser();
    std::string getTypeName() const override;
};

#endif // LASER_HPP
