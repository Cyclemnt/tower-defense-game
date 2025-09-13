#ifndef CORE_STORAGE_HPP
#define CORE_STORAGE_HPP

#include "tile.hpp"

class CoreStorage: private Tile {
private:
    /* data */
    
public:
    CoreStorage(int x, int y);
    ~CoreStorage();

    bool isWalkable() const override;
    bool isBuildable() const override;

    std::string getTypeName() const override;
};

#endif // CORE_STORAGE_HPP
