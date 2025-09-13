#ifndef CORES_HPP
#define CORES_HPP

class Cores {
private:
    // Where are they?
    int safe;
    int stolen;
    int lost;

public:
    Cores(/* args */);
    ~Cores();
    
    void stealCore();
    void returnCore();
    void loseCore();
};

#endif // CORES_HPP
