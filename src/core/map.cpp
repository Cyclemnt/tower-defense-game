#include <stdexcept>
#include "core/map.hpp"
#include "core/interfaces/iMapSource.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

namespace tdg::core {

    Map::Map(std::shared_ptr<IMapSource> source) {
        // Load Map
        MapData data = source->loadMap();
        m_width = data.width;
        m_height = data.height;
        m_tiles = data.tiles;
        m_level = data.level;

        // Save interest points for fast access
        for (Tile& tile : m_tiles) {
            switch (tile.type) {
                case Tile::Type::Entry: m_entryPoints.push_back(&tile); break;
                case Tile::Type::Exit:  m_exitPoints.push_back(&tile);  break;
                case Tile::Type::CoreStorage: m_corePoint = &tile; break;
                default: break;
            }
        }        

        if (m_exitPoints.empty()) m_exitPoints = m_entryPoints; // If no explicit exits, fallback to entries.
        if (m_entryPoints.empty()) throw std::runtime_error("Wrong initialization of the map: no entry point");
        else if (!m_corePoint) throw std::runtime_error("Wrong initialization of the map: no core storage");
    }

    const Tile* Map::tileAt(int x, int y) const noexcept {
        if (x < 0 || y < 0 || x >= m_width || y >= m_height) return nullptr;
        return &m_tiles[y * m_width + x];
    }

    Tile* Map::tileAt(int x, int y) noexcept {
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

                if (const Tile* t = tileAt(nx, ny)) result.push_back(t);
            }
        }

        return result;
    }

    bool Map::canRecieveTowerAt(int x, int y) const noexcept {
        const Tile* tile = tileAt(x, y);
        if (!tile) return false;
        bool tileIsOpen = tile->type == Tile::Type::Open;
        bool hasTower = tile->hasTower;
        return tileIsOpen && !hasTower;
    }

    bool Map::hasTowerAt(int x, int y) const noexcept {
        const Tile* tile = tileAt(x, y);
        if (!tile) return false;
        return tile->hasTower;
    }

    bool Map::markTowerAt(int x, int y) noexcept {
        Tile* tile = tileAt(x, y);
        if (!tile) return false;

        if (tile->type == Tile::Type::Open && !tile->hasTower) {
            tile->hasTower = true;
            return true;
        }
        return false;
    }

    bool Map::removeTowerAt(int x, int y) noexcept {
        Tile* tile = tileAt(x, y);
        if (!tile) return false;

        if (tile->hasTower) {
            tile->hasTower = false;
            return true;
        }
        return false;
    }

    void Map::setCoreStorageFillRatioRequest(std::function<float()> callback) noexcept {
        onCoreStorageFillRatioRequest = callback;
    }

    void Map::draw(IVideoRenderer& vidRenderer) const {
        // Draw map tiles
        for (size_t i = 0; i < m_tiles.size(); i++) {
            int x = i % m_width;
            int y = i / m_width;
            vidRenderer.drawSprite(tileToSpriteId(m_tiles[i]), x, y);
        }

        // Draw margins
        const int margin = 5;
        // Top and bottom
        for (int i = -margin; i < m_width + margin; i++) {
            for (int j = -margin; j < 0; ++j) {
                vidRenderer.drawSprite("tiles/" + std::to_string(m_level) + "/empty_" + randomTextureId(i, j), i, j);  // Top
            }
            for (int j = m_height; j < m_height + margin; j++) {
                vidRenderer.drawSprite("tiles/" + std::to_string(m_level) + "/empty_" + randomTextureId(i, j), i, j);  // Bottom
            }
        }

        // Left and right
        for (int i = -margin; i < 0; i++) {
            for (int j = -margin; j < m_height + margin; j++) {
                vidRenderer.drawSprite("tiles/" + std::to_string(m_level) + "/empty_" + randomTextureId(i, j), i, j);  // Left
            }
        }
        for (int i = m_width; i < m_width + margin; i++) {
            for (int j = -margin; j < m_height + margin; j++) {
                vidRenderer.drawSprite("tiles/" + std::to_string(m_level) + "/empty_" + randomTextureId(i, j), i, j);  // Right
            }
        }
    }

    std::string Map::tileToSpriteId(Tile tile) const noexcept {
        switch (tile.type) {
            case Tile::Type::Path: return "tiles/" + std::to_string(m_level) + "/path";
            case Tile::Type::Open: return "tiles/" + std::to_string(m_level) + "/open";
            case Tile::Type::Entry: return "tiles/" + std::to_string(m_level) + "/entry";
            case Tile::Type::Exit: return "tiles/" + std::to_string(m_level) + "/exit";
            case Tile::Type::CoreStorage: return "tiles/" + std::to_string(m_level) + "/core_" + coreStorageTextureId();
            case Tile::Type::Empty: return "tiles/" + std::to_string(m_level) + "/empty_" + randomTextureId(tile.x, tile.y);
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
        if (!onCoreStorageFillRatioRequest) return "0";
        float filled = onCoreStorageFillRatioRequest();
        if (filled == 1.0f) return "0";
        else if (filled > 0.5f) return "1";
        else if (filled > 0.0f) return "2";
        else return "3";
    }

} // namespace tdg::core

