#ifndef MAP_HPP
#define MAP_HPP

#include "interfaces/iMapSource.hpp"
#include <vector>

namespace tdg::core {

    enum class TileType { Path, Open, Entry, Exit, CoreStorage, Empty };

    struct Tile {
        int x{0}, y{0};
        TileType type{TileType::Empty};
        bool hasTower{false};
    };

    /// @brief Map stores tile layout and provides queries. Domain-only.
    class Map {
    public:
        explicit Map(const MapData& data);

        int width() const noexcept { return m_width; }
        int height() const noexcept { return m_height; }

        const Tile* tileAt(int x, int y) const;
        Tile* tileAt(int x, int y);

        std::vector<Tile*> neighbors(int x, int y) const;

        std::vector<std::pair<int,int>> entryPoints() const;
        std::vector<std::pair<int,int>> corePoints() const;

        bool placeTower(int x, int y);
        bool removeTower(int x, int y);

    private:
        int m_width{0};
        int m_height{0};
        std::vector<Tile> m_tiles; // row-major
    };

} // namespace tdg::core

#endif // MAP_HPP