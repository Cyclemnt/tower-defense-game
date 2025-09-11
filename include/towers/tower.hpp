#ifndef TOWER_HPP
#define TOWER_HPP

class Tower {
private:
    // Cost of the tower
    int priceAu;
    int priceAg;
    int priceCu;

    // Specifications of the tower
    int damage;
    int speed;
    int range;

    // Does it go kaboom?
    bool areaDamage;

    // Level of the tower
    int level;

public:
    Tower(/* args */);
    ~Tower();
};

#endif // TOWER_HPP
