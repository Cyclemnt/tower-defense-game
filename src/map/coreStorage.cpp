#include "../../include/map/coreStorage.hpp"

CoreStorage::CoreStorage(int x, int y)
    : Tile(x, y) {}

CoreStorage::~CoreStorage() {}

bool CoreStorage::isWalkable() const {
    return true;
}

bool CoreStorage::isBuildable() const {
    return false;
}

std::string CoreStorage::getTypeName() const {
    return "CoreStorage";
}
