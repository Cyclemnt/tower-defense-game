#include "../../include/map/openZone.hpp"

OpenZone::OpenZone(int x, int y)
    : Tile(x, y), occupied(false) {}

OpenZone::~OpenZone() {}

bool OpenZone::isWalkable() const {
    return true;
}

bool OpenZone::isBuildable() const {
    return !occupied;
}

void OpenZone::setOccupied(bool value) {
    occupied = value;
}

std::string OpenZone::getTypeName() const {
    return "OpenZone";
}

bool OpenZone::isOccupied() const {
    return occupied;
}

void OpenZone::setOccupied(bool value) {
    occupied = value;
}
