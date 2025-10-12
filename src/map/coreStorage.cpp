#include "../../include/map/coreStorage.hpp"
#include "../../include/resources/cores.hpp"

CoreStorage::CoreStorage(int x, int y, Cores* coresptr)
    : Tile(x, y), cores(coresptr) {}

bool CoreStorage::isWalkable() const { return true; }

bool CoreStorage::isBuildable() const { return false; }

std::string CoreStorage::getTypeName() const { return "CoreStorage"; }

int CoreStorage::getCoreCount() const { return cores->getSafe(); }

int CoreStorage::takeCores(int requested) { return cores->stealCore(requested); }

void CoreStorage::depositCores(int n) { cores->returnCore(n); }
