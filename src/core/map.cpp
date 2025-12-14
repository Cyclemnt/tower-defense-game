#include <stdexcept>
#include <iostream>
#include "core/map.hpp"
#include "core/interfaces/iMapSource.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

namespace tdg::core {

    Map::Map(std::shared_ptr<IMapSource> source) {
        MapData data = source->loadMap();
        m_width = data.width;
        m_height = data.height;
        m_tiles = data.tiles;

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

    void Map::setCoreStorageFillRatio(float ratio) {
        coreStorageFillRatio = ratio;
    }

    void Map::draw(IVideoRenderer& vidRenderer) const {
        for (size_t i = 0; i < m_tiles.size(); i++) {
            int x = i % m_width;
            int y = i / m_width;
            vidRenderer.drawSprite(tileToSpriteId(m_tiles[i]), x, y);
        }
    }

    std::string Map::tileToSpriteId(Tile t) const {
        switch (t.type) {
            case Tile::Type::Path: return "tiles/path";
            case Tile::Type::Open: return "tiles/open";
            case Tile::Type::Entry: return "tiles/entry";
            case Tile::Type::Exit: return "tiles/exit";
            case Tile::Type::CoreStorage: return "tiles/core_" + coreStorageTextureId();
            case Tile::Type::Empty: return "tiles/empty_" + randomTextureId(t.x, t.y);
            default: return "missing_texture";
        }
    }

    std::string Map::randomTextureId(int x, int y) const noexcept {
        const uint32_t combined = static_cast<uint32_t>((x * 73857093U) ^ (y * 19349663U) + kSeed);
        const uint32_t rnd = combined % 100U;

        if (rnd < 70U) return "1";
        else if (rnd < 72U) return "2";
        else if (rnd < 74U) return "4";
        else if (rnd < 76U) return "5";
        else if (rnd < 78U) return "6";
        else if (rnd < 80U) return "7";
        else if (rnd < 90U) return "3";
        else if (rnd < 91U) return "8";
        else return "0";
    }

    std::string Map::coreStorageTextureId() const noexcept {
        if (coreStorageFillRatio == 1.0f) return "0";
        else if (coreStorageFillRatio > 0.5f) return "1";
        else if (coreStorageFillRatio > 0.0f) return "2";
        else return "3";
    }

} // namespace tdg::core