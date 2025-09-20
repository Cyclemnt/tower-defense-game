#include "../../include/map/coreStorage.hpp"

CoreStorage::CoreStorage(int x, int y, int initialCores)
    : Tile(x, y), cores(initialCores) {}

bool CoreStorage::isWalkable() const { return true; }

bool CoreStorage::isBuildable() const { return false; }

std::string CoreStorage::getTypeName() const { return "CoreStorage"; }

int CoreStorage::getCoreCount() const { return cores; }

int CoreStorage::takeCores(int requested) {
    if (requested <= 0) return 0;
    int taken = std::min(requested, cores);
    cores -= taken;
    return taken;
}

void CoreStorage::depositCores(int n) {
    if (n <= 0) return;
    cores += n;
}
