#include <fstream>
#include <sstream>
#include <memory>
#include "infrastructure/fileMapSource.hpp"
#include "core/map.hpp"

namespace tdg::infra {
    
    FileMapSource::FileMapSource(std::string folderPath)
        : m_folderPath(folderPath) {}

    core::MapData FileMapSource::loadMap(unsigned int level) const {
        std::string filename = m_folderPath + std::to_string(level) + ".txt";
        std::ifstream file(filename);
        if (!file.is_open())
            throw std::runtime_error("[FileMapSource] Cannot open map file: " + filename);

        std::vector<std::string> lines;
        std::string line;

        // Read all lines first
        while (std::getline(file, line)) {
            std::string filtered;
            for (char c : line)
                if (!std::isspace(static_cast<unsigned char>(c)))
                    filtered.push_back(c);

            if (!filtered.empty())
                lines.push_back(std::move(filtered));
        }
        
        file.close();

        if (lines.empty())
            throw std::runtime_error("[FileMapSource] Map file is empty: " + filename);

        // Determine width and height
        int height = static_cast<int>(lines.size());
        int width = static_cast<int>(lines[0].size());

        for (const auto& l : lines)
            if (static_cast<int>(l.size()) != width)
                throw std::runtime_error("[FileMapSource] Inconsistent line width in map file: " + filename);

        core::MapData mapData;
        mapData.height = height;
        mapData.width = width;

        // Parse and instantiate tiles
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                char c = lines[y][x];
                core::Tile tile;

                switch (c) {
                    case '#': tile = {x, y, core::TileType::Path}; break;
                    case 'O': tile = {x, y, core::TileType::Open}; break;
                    case 'E': tile = {x, y, core::TileType::Entry}; break;
                    case 'X': tile = {x, y, core::TileType::Exit}; break;
                    case 'C': tile = {x, y, core::TileType::CoreStorage}; break;
                    case '.': [[fallthrough]];
                    default: tile = {x, y, core::TileType::Empty}; break;
                }

                mapData.tiles.push_back(tile);
            }
        }
    }

} // namespace tdg::infra
