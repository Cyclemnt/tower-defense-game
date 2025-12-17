#include "core/tile.hpp"

namespace tdg::core {

    Tile::Tile(int px, int py, Type t) : x(px), y(py), type(t) {}
    
    bool Tile::walkable(bool ignoreTower) const noexcept {
        // Every tile except Tile::Empty are walkable
        return (type != Type::Empty && (ignoreTower || !hasTower));
    }
    
} // namespace tdg::core
