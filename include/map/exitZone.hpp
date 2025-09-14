#ifndef EXIT_ZONE_HPP
#define EXIT_ZONE_HPP

#include "tile.hpp"

class ExitZone: public Tile {
public:
    ExitZone(int x, int y);
    ~ExitZone();

    bool isWalkable() const override;
    bool isBuildable() const override;

    std::string getTypeName() const override;
};

#endif // EXIT_ZONE_HPP
