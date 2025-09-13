#include "../../include/map/emptyZone.hpp"

EmptyZone::EmptyZone(int x, int y)
    : Tile(x, y) {}

EmptyZone::~EmptyZone() {}

bool EmptyZone::isWalkable() const {
    return false;
}

bool EmptyZone::isBuildable() const {
    return false;
}

std::string EmptyZone::getTypeName() const {
    return "EmptyZone";
}
