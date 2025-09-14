#ifndef CORES_HPP
#define CORES_HPP

class Cores {
private:
    // Where are they?
    int safe;
    int stolen;
    int lost;

public:
    Cores(int initial = 24);
    ~Cores();
    
    void stealCore(int n);   // Enemy steals cores from base
    void returnCore(int n);  // Enemy carrying cores dies → cores return
    void loseCore(int n);    // Enemy exits with cores → they are permanently lost
};

#endif // CORES_HPP
