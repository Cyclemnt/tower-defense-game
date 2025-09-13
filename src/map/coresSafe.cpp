#include "../../include/map/coresSafe.hpp"

CoresSafe::CoresSafe(int x, int y)
    : Tile(x, y) {}

CoresSafe::~CoresSafe() {}

bool CoresSafe::isWalkable() const {
    return true;
}

bool CoresSafe::isBuildable() const {
    return false;
}
