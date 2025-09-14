#ifndef ENTRY_ZONE_HPP
#define ENTRY_ZONE_HPP

#include "tile.hpp"

class EntryZone: public Tile {
private:
    /* data */
    
public:
    EntryZone(int x, int y);
    ~EntryZone();

    bool isWalkable() const override;
    bool isBuildable() const override;

    std::string getTypeName() const override;
};

#endif // ENTRY_ZONE_HPP
