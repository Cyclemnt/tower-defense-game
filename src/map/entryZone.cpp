#include "../../include/map/entryZone.hpp"

EntryZone::EntryZone(int x, int y)
    : Tile(x, y) {}

EntryZone::~EntryZone() {}

bool EntryZone::isWalkable() const {
    return true;
}

bool EntryZone::isBuildable() const {
    return false;
}
