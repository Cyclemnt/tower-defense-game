#include <stdexcept>
#include "include/core/map.hpp"

namespace tdg::core {

    Map::Map(const MapData& data)
        : m_width(data.width), m_height(data.height)
    {
        for (const auto& t : data.tiles) {
            m_tiles.push_back(t);

            if (t.type == TileType::Entry) {
                m_entryPoints.push_back(&m_tiles.back());
            }
            else if (t.type == TileType::Exit) {
                m_exitPoints.push_back(&m_tiles.back());
            }
            else if (t.type == TileType::CoreStorage) {
                m_corePoint = &m_tiles.back();
            }
        }

        if (m_exitPoints.empty()) m_exitPoints = m_entryPoints; // If no explicit exits, fallback to entries.

        if (m_entryPoints.empty()) throw std::runtime_error("Wrong initialization of the map: no entry point");
        else if (!m_corePoint) throw std::runtime_error("Wrong initialization of the map: no core storage");
    }

    const Tile* Map::tileAt(int x, int y) const {
        if (x < 0 || y < 0 || x >= m_width || y >= m_height) return nullptr;
        return &m_tiles[y * m_width + x];
    }

    Tile* Map::tileAt(int x, int y) {
        if (x < 0 || y < 0 || x >= m_width || y >= m_height) return nullptr;
        return &m_tiles[y * m_width + x];
    }

    std::vector<const Tile*> Map::neighbors(const Tile* tile) const {
        std::vector<const Tile*> result;

        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == dy) { continue; } // Do not include diagonals
                int nx = tile->x + dx;
                int ny = tile->y + dy;

                if (const Tile* t = tileAt(nx, ny))
                    result.push_back(t);
            }
        }

        return result;
    }

    bool Map::placeTower(int x, int y) {
        Tile* t = tileAt(x, y);
        if (!t) return false;

        if (t->type == TileType::Open && !t->hasTower) {
            tileAt(x, y)->hasTower = true;
            return true;
        }
        return false;
    }

    bool Map::removeTower(int x, int y) {
        Tile* t = tileAt(x, y);
        if (!t) return false;

        if (t->type == TileType::Open && t->hasTower) {
            tileAt(x, y)->hasTower = false;
            return true;
        }
        return false;
    }

} // namespace tdg::core