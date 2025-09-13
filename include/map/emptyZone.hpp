#ifndef EMPTY_ZONE_HPP
#define EMPTY_ZONE_HPP

#include "tile.hpp"

class EmptyZone: private Tile {
private:
    /* data */
    
public:
    EmptyZone(int x, int y);
    ~EmptyZone();

    bool isWalkable() const override;
    bool isBuildable() const override;

    std::string getTypeName() const override;
};

#endif // EMPTY_ZONE_HPP
