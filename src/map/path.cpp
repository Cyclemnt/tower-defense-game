#include "../../include/map/path.hpp"

Path::Path(int x, int y)
    : Tile(x, y) {}

Path::~Path() {}

bool Path::isWalkable() const { return true; }

bool Path::isBuildable() const { return false; }

std::string Path::getTypeName() const { return "Path"; }
