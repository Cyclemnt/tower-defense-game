#include <fstream>
#include <sstream>
#include <stdexcept>
#include "infrastructure/fileMapSource.hpp"
#include "core/tile.hpp"

namespace tdg::infra {
    
    FileMapSource::FileMapSource(std::string folderPath)
        : m_folderPath(folderPath)
    {
        setLevel(1u);
    }

    void FileMapSource::setLevel(unsigned int level) {
        m_level = level;
        m_filePath = m_folderPath + "map_" + std::to_string(level) + ".txt";
    }

    core::MapData FileMapSource::loadMap() const {
        std::ifstream file(m_filePath);
        if (!file.is_open())
            throw std::runtime_error("Failed to open map file: " + m_filePath);

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
            throw std::runtime_error("Map file is empty: " + m_filePath);

        // Determine width and height
        int height = static_cast<int>(lines.size());
        int width = static_cast<int>(lines[0].size());

        for (const auto& l : lines)
            if (static_cast<int>(l.size()) != width)
                throw std::runtime_error("Inconsistent line width in map file: " + m_filePath);

        core::MapData mapData;
        mapData.height = height;
        mapData.width = width;
        mapData.level = m_level;

        // Parse and instantiate tiles
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                char c = lines[y][x];
                core::Tile tile;

                switch (c) {
                    case '#': tile = {x, y, core::Tile::Type::Path}; break;
                    case 'O': tile = {x, y, core::Tile::Type::Open}; break;
                    case 'E': tile = {x, y, core::Tile::Type::Entry}; break;
                    case 'X': tile = {x, y, core::Tile::Type::Exit}; break;
                    case 'C': tile = {x, y, core::Tile::Type::CoreStorage}; break;
                    case '.': [[fallthrough]];
                    default: tile = {x, y, core::Tile::Type::Empty}; break;
                }

                mapData.tiles.push_back(tile);
            }
        }
        return mapData;
    }

} // namespace tdg::infra
