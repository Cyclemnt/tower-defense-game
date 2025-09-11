#ifndef CREATURE_HPP
#define CREATURE_HPP

class Creature {
private:
    // Specifications of the creature
    int health;
    int shield;
    int speed;

    // Amount of cores currently on the creature
    int cores;
    
public:
    Creature(/* args */);
    ~Creature();
};

#endif // CREATURE_HPP
