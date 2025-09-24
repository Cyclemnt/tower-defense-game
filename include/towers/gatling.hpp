#ifndef GATLING_HPP
#define GATLING_HPP

#include "tower.hpp"

class Gatling : public Tower
{
private:
    /* data */
public:
    Gatling(int x_, int y_);
    ~Gatling();
    std::string getTypeName() const override;
};

#endif // GATLING_HPP
