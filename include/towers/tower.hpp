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

    // Does it do area damage?
    bool areaDamage;

    // Level of the tower
    int level;

public:
    Tower(/* args */);
    ~Tower();

    
    void attack() const;
    void upgrade();
};

#endif // TOWER_HPP
