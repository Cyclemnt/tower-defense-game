#include "../../include/map/exitZone.hpp"

ExitZone::ExitZone(int x, int y)
    : Tile(x, y) {}

ExitZone::~ExitZone() {}

bool ExitZone::isWalkable() const {
    return true;
}

bool ExitZone::isBuildable() const {
    return false;
}

std::string ExitZone::getTypeName() const {
    return "ExitZone";
}
