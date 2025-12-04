#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "interfaces/iMapSource.hpp"

namespace tdg::core {

    enum class TileType { Path, Open, Entry, Exit, CoreStorage, Empty };

    struct Tile {
        int x{0}, y{0};
        TileType type{TileType::Empty};
        bool hasTower{false};

        Tile(int px = 0, int py = 0, TileType t = TileType::Empty) : x(px), y(py), type(t) {}
        bool walkable() const { return (type == TileType::Path || type == TileType::Open && !hasTower); }
        bool buildable() const { return (type == TileType::Open && !hasTower); }
        bool sellable() const { return (type == TileType::Open && hasTower); }
    };

    /// @brief Map stores tile layout and provides queries. Domain-only.
    class Map {
    public:
        explicit Map(const MapData& data);

        int width() const noexcept { return m_width; }
        int height() const noexcept { return m_height; }

        const Tile* tileAt(int x, int y) const;
        Tile* tileAt(int x, int y);

        std::vector<const Tile*> neighbors(const Tile* tile) const;

        std::vector<Tile*> entryPoints() const { return m_entryPoints; }
        std::vector<Tile*> exitPoints() const { return m_exitPoints; }
        Tile* corePoint() const { return m_corePoint; }

        bool placeTower(int x, int y);
        bool removeTower(int x, int y);

    private:
        int m_width{0};
        int m_height{0};
        std::vector<Tile> m_tiles; // row-major

        std::vector<Tile*> m_entryPoints;
        std::vector<Tile*> m_exitPoints;
        Tile* m_corePoint = nullptr;
    };

} // namespace tdg::core

#endif // MAP_HPP