#ifndef TILE_HPP
#define TILE_HPP

namespace tdg::core {
    
    struct Tile final {
            enum class Type { Path, Open, Entry, Exit, CoreStorage, Empty };

            Tile() = default;
            Tile(int px, int py, Type t = Type::Empty);

            bool walkable(bool ignoreTower) const noexcept;

            int x{0};
            int y{0};
            Type type{Type::Empty};
            bool hasTower{false};
    };

} // namespace tdg::core

#endif // TILE_HPP