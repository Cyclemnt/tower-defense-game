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

    std::array<int, 3> getBalance() const;
    void add(std::array<int, 3> amounts);
    void spend(std::array<int, 3> amounts);
};

#endif // MATERIALS_HPP

