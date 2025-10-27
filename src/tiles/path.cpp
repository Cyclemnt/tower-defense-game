#include "../../include/tiles/path.hpp"

Path::Path(sf::Vector2i position_)
    : Tile(position_) {}

Path::~Path() {}

bool Path::isWalkable() const { return true; }

bool Path::isBuildable() const { return false; }

std::string Path::getTextureName() const { return "tile_path.png"; }
