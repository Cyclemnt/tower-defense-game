#include "../../include/map/map.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>

Map::Map(int w, int h) : width(w), height(h) {
    grid.resize(height);
    for (int y = 0; y < height; ++y) {
        grid[y].resize(width);
        for (int x = 0; x < width; ++x) {
            grid[y][x] = std::make_unique<EmptyZone>(x, y);
        }
    }
    grid[0][0] = std::make_unique<EmptyZone>(0, 0);
}

Map::~Map() {}

int Map::getWidth() const { return width; }

int Map::getHeight() const { return height; }

Tile* Map::getTile(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Invalid tile coordinates");
    }
    return grid[y][x].get();
}

void Map::placeTile(std::unique_ptr<Tile> tile) {
    int x = tile->getX();
    int y = tile->getY();

    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Invalid tile coordinates");
    }

    // If it was an interest point, remove from the right vector
    if (EntryZone* e = dynamic_cast<EntryZone*>(grid[y][x].get())) {
        // Using std::find to find the tile to delete
        auto it = std::find(entries.begin(), entries.end(), e);
        if (it != entries.end()) {
            entries.erase(it);
        }
    } else if (ExitZone* ex = dynamic_cast<ExitZone*>(grid[y][x].get())) {
        // Using std::find to find the tile to delete
        auto it = std::find(exits.begin(), exits.end(), ex);
        if (it != exits.end()) {
            exits.erase(it);
        }
    } else if (CoreStorage* c = dynamic_cast<CoreStorage*>(grid[y][x].get())) {
        coreStorage = nullptr;
    }

    // Replace the tile
    grid[y][x] = std::move(tile);

    // If it is an interest point, add to the right vector
    if (EntryZone* e = dynamic_cast<EntryZone*>(grid[y][x].get())) {
        entries.push_back(e);
    } else if (ExitZone* ex = dynamic_cast<ExitZone*>(grid[y][x].get())) {
        exits.push_back(ex);
    } else if (CoreStorage* c = dynamic_cast<CoreStorage*>(grid[y][x].get())) {
        coreStorage = c;
    }
}

const std::vector<EntryZone*>& Map::getEntries() const { return entries; }

const std::vector<ExitZone*>& Map::getExits() const { return exits; }

CoreStorage* Map::getCoreStorage() const { return coreStorage; }

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
