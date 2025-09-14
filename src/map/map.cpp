#include "../../include/map/map.hpp"
#include <stdexcept>
#include <iostream>

Map::Map(int w, int h) : width(w), height(h) {
    grid.resize(height);
    for (int y = 0; y < height; ++y) {
        grid[y].resize(width);
        for (int x = 0; x < width; ++x) {
            grid[y][x] = std::make_unique<EmptyZone>(x, y);
        }
    }
}

Map::~Map() {}

// Return map dimensions
int Map::getWidth() const { return width; }
int Map::getHeight() const { return height; }

// Return pointer to the (x, y) tile
Tile* Map::getTile(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Invalid tile coordinates");
    }
    return grid[y][x].get();
}

const std::vector<EntryZone*>& Map::getEntries() const { return entries; }
const std::vector<ExitZone*>& Map::getExits() const { return exits; }
const CoreStorage* Map::getCoreStorage() const { return coreStorage; }

std::vector<Tile*> Map::getNeighbors(Tile* tile) const {
    std::vector<Tile*> neighbors;
    int x = tile->getX();
    int y = tile->getY();

    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
            neighbors.push_back(grid[ny][nx].get());
        }
    }
    return neighbors;
}

std::vector<Tile*> Map::findPath(Creature* c) const {
    std::vector<Tile*> path;
    return path;
}

void Map::printMap() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            char symbol = '.';
            if (dynamic_cast<Path*>(grid[y][x].get())) symbol = '#';
            else if (dynamic_cast<OpenZone*>(grid[y][x].get())) symbol = 'O';
            else if (dynamic_cast<EntryZone*>(grid[y][x].get())) symbol = 'E';
            else if (dynamic_cast<ExitZone*>(grid[y][x].get())) symbol = 'X';
            else if (dynamic_cast<CoreStorage*>(grid[y][x].get())) symbol = 'C';

            std::cout << symbol << " ";
        }
        std::cout << "\n";
    }
}
