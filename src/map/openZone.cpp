#include "../../include/map/openZone.hpp"

OpenZone::OpenZone(int x, int y)
    : Tile(x, y), occupied(false) {}

OpenZone::~OpenZone() {}

bool OpenZone::isWalkable() const { return !occupied; }

bool OpenZone::isBuildable() const { return true; }

std::string OpenZone::getTextureName() const { return "tile_open.png"; }

bool OpenZone::isOccupied() const { return occupied; }

void OpenZone::setOccupied(bool value) { occupied = value; }
