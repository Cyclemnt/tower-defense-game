#include <stdexcept>
#include "include/core/map.hpp"

using namespace tdg::core;

Map::Map(const MapData& data) {
    m_width = data.width;
    m_height = data.height;

    for (size_t i = 0; i < data.tiles.size(); ++i) {
        m_tiles.push_back(data.tiles[i]);

        if (data.tiles[i].type == TileType::Entry) {
            m_entryPoints.push_back(&m_tiles.back());
        }
        else if (data.tiles[i].type == TileType::Exit) {
            m_exitPoints.push_back(&m_tiles.back());
        }
        else if (data.tiles[i].type == TileType::CoreStorage) {
            m_corePoint = &m_tiles.back();
        }
    }

    if (m_exitPoints.empty()) m_exitPoints = m_entryPoints;

    if (m_entryPoints.empty()) throw std::runtime_error("Wrong initialization of the map: no entry point");
    else if (!m_corePoint) throw std::runtime_error("Wrong initialization of the map: no core storage");
}

const Tile* Map::tileAt(int x, int y) const {
    return &m_tiles[y * m_width + x];
}

Tile* Map::tileAt(int x, int y) {
    return &m_tiles[y * m_width + x];
}

std::vector<const Tile*> Map::neighbors(int x, int y) const {
    std::vector<const Tile*> neighbors;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) { continue; } // Do not include center tile
            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < m_width && ny >= 0 && ny < m_height) {
                neighbors.push_back(tileAt(nx, ny));
            }
        }
    }

    return neighbors;
}

bool Map::placeTower(int x, int y) {
    Tile* t = tileAt(x, y);

    if (t->type == TileType::Open && !t->hasTower) {
        tileAt(x, y)->hasTower = true;
        return true;
    } else {
        return false;
    }
}

bool Map::removeTower(int x, int y) {
    Tile* t = tileAt(x, y);

    if (t->type == TileType::Open && t->hasTower) {
        tileAt(x, y)->hasTower = false;
        return true;
    } else {
        return false;
    }
}