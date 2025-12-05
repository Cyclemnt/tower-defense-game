#include <stdexcept>
#include <iostream>
#include "core/map.hpp"
#include "core/interfaces/iMapSource.hpp"

namespace tdg::core {

    Map::Map(const MapData& data)
        : m_width(data.width), m_height(data.height), m_tiles(data.tiles)
    {
        for (Tile& t : m_tiles) {
            if (t.type == Tile::Type::Entry) {
                m_entryPoints.push_back(&t);
            }
            else if (t.type == Tile::Type::Exit) {
                m_exitPoints.push_back(&t);
            }
            else if (t.type == Tile::Type::CoreStorage) {
                m_corePoint = &t;
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
                if (dx == dy || dx == -dy) { continue; } // Do not include diagonals
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

        if (t->type == Tile::Type::Open && !t->hasTower) {
            tileAt(x, y)->hasTower = true;
            return true;
        }
        return false;
    }

    bool Map::removeTower(int x, int y) {
        Tile* t = tileAt(x, y);
        if (!t) return false;

        if (t->type == Tile::Type::Open && t->hasTower) {
            tileAt(x, y)->hasTower = false;
            return true;
        }
        return false;
    }

    void Map::printMap() const {
        for (int y = 0; y < m_height; ++y) {
            for (int x = 0; x < m_width; ++x) {
                char symbol = '.';
                if (tileAt(x, y)->type == Tile::Type::Path) symbol = '#';
                else if (tileAt(x, y)->type == Tile::Type::Open) symbol = 'O';
                else if (tileAt(x, y)->type == Tile::Type::Entry) symbol = 'E';
                else if (tileAt(x, y)->type == Tile::Type::Exit) symbol = 'X';
                else if (tileAt(x, y)->type == Tile::Type::CoreStorage) symbol = 'C';

                std::cout << symbol << " ";
            }
            std::cout << "\n";
        }
    }

} // namespace tdg::core