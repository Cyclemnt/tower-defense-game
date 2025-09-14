#ifndef CORE_STORAGE_HPP
#define CORE_STORAGE_HPP

#include "tile.hpp"

class CoreStorage: public Tile {
private:
    int cores; // number of cores currently stored here
    
public:
    CoreStorage(int x, int y, int initialCores = 0);
    ~CoreStorage() override = default;

    bool isWalkable() const override;
    bool isBuildable() const override;

    // Return Tile type name
    std::string getTypeName() const override;

    // Return current number of cores on this tile
    int getCoreCount() const;

    // Attempt to take up to 'requested' cores from this tile.
    // Returns the actual number taken (0..requested).
    // This method modifies the internal cores count.
    int takeCores(int requested);

    // Put back `n` cores onto this tile (n >= 0).
    void depositCores(int n);
};

#endif // CORE_STORAGE_HPP
