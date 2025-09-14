#ifndef OPEN_ZONE_HPP
#define OPEN_ZONE_HPP

#include "tile.hpp"

class OpenZone: public Tile {
private:
    // Occupied by a tower
    bool occupied;
    
public:
    OpenZone(int x, int y);
    ~OpenZone();

    bool isWalkable() const override;
    bool isBuildable() const override;

    std::string getTypeName() const override;

    bool isOccupied() const;
    void setOccupied(bool value);
};

#endif // OPEN_ZONE_HPP
