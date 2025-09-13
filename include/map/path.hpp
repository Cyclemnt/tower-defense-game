#ifndef PATH_HPP
#define PATH_HPP

#include "tile.hpp"

class Path: private Tile {
private:
    /* data */
    
public:
    Path(int x, int y);
    ~Path();

    bool isWalkable() const override;
    bool isBuildable() const override;

    std::string getTypeName() const override;
};

#endif // PATH_HPP
