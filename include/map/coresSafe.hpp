#ifndef CORES_SAFE_HPP
#define CORES_SAFE_HPP

#include "tile.hpp"

class CoresSafe: private Tile {
private:
    /* data */
    
public:
    CoresSafe(int x, int y);
    ~CoresSafe();

    bool isWalkable() const override;
    bool isBuildable() const override;

    std::string getTypeName() const override;
};

#endif // CORES_SAFE_HPP
