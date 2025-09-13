#include "../../include/map/map.hpp"

Map::Map() {
    /* Map initialization depending on the level */
}

Map::~Map() {}

void Map::getTile(int x, int y) const {
}

void Map::getNeighbors(Tile*) const {
}

std::vector<Tile*> Map::findPath(Creature* c) const {
    std::vector<Tile*> path;
    return path;
}
