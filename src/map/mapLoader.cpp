#include <fstream>
#include <sstream>
#include <vector>
#include "../include/map/mapLoader.hpp"
#include "../../include/map/coreStorage.hpp"
#include "../../include/map/emptyZone.hpp"
#include "../../include/map/entryZone.hpp"
#include "../../include/map/exitZone.hpp"
#include "../../include/map/map.hpp"
#include "../../include/map/openZone.hpp"
#include "../../include/map/path.hpp"
#include "../../include/resources/cores.hpp"


void MapLoader::loadFromFile(Map& map, const std::string& filename, Cores* cores) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open map file: " + filename);
    }

    std::vector<std::string> lines;
    std::string line;

    // --- Read all lines first ---
    while (std::getline(file, line)) {
        // Remove leading/trailing spaces
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string filtered;
        char c;
        while (iss >> c) filtered.push_back(c); // ignore spaces and tabs
        if (!filtered.empty())
            lines.push_back(filtered);
    }

    file.close();

    if (lines.empty())
        throw std::runtime_error("Map file is empty: " + filename);

    // --- Determine width and height ---
    int height = static_cast<int>(lines.size());
    int width = static_cast<int>(lines[0].size());
    for (const auto& l : lines)
        if ((int)l.size() != width)
            throw std::runtime_error("Inconsistent line width in map file: " + filename);

    // --- Resize map dynamically ---
    map.resize(width, height);

    // --- Parse and place tiles ---
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            char c = lines[y][x];
            std::unique_ptr<Tile> tile;

            switch (c) {
                case '#': tile = std::make_unique<Path>(x, y); break;
                case 'O': tile = std::make_unique<OpenZone>(x, y); break;
                case 'E': tile = std::make_unique<EntryZone>(x, y); break;
                case 'X': tile = std::make_unique<ExitZone>(x, y); break;
                case 'C':
                    if (cores)
                        tile = std::make_unique<CoreStorage>(x, y, cores);
                    else
                        tile = std::make_unique<EmptyZone>(x, y);
                    break;
                case '.': [[fallthrough]];
                default:
                    tile = std::make_unique<EmptyZone>(x, y);
                    break;
            }

            map.placeTile(std::move(tile));
        }
    }
}
