#include "../../include/map/tile.hpp"

Tile::Tile(int x_, int y_)
    : x(x_), y(y_) {}

int Tile::getX() const { return x; }

int Tile::getY() const { return y; }
