#ifndef MATERIALS_HPP
#define MATERIALS_HPP

#include "../towers/tower.hpp"
#include <array>

class Materials {
private:
    // Three types (inspired from periodic table: gold, silver, copper)
    int au;
    int ag;
    int cu;

public:
    Materials(/* args */);
    ~Materials();

    void add(std::array<int, 3> amounts);
    void spend(std::array<int, 3> amounts);
    bool canAfford(Tower t) const;
};

#endif // MATERIALS_HPP

