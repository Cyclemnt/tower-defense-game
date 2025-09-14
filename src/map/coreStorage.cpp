#include "../../include/map/coreStorage.hpp"

CoreStorage::CoreStorage(int x, int y, int initialCores)
    : Tile(x, y), cores(initialCores) {}

//CoreStorage::~CoreStorage() {}

bool CoreStorage::isWalkable() const {
    return true;
}

bool CoreStorage::isBuildable() const {
    return false;
}

// Return Tile type name
std::string CoreStorage::getTypeName() const {
    return "CoreStorage";
}

// Return current number of cores on this tile
int CoreStorage::getCoreCount() const { return cores; }

// Attempt to take up to 'requested' cores from this tile.
// Returns the actual number taken (0..requested).
// This method modifies the internal cores count.
int CoreStorage::takeCores(int requested) {
    if (requested <= 0) return 0;
    int taken = std::min(requested, cores);
    cores -= taken;
    return taken;
}

// Put back 'n' cores onto this tile (n >= 0).
void CoreStorage::depositCores(int n) {
    if (n <= 0) return;
    cores += n;
}