#include <iostream>
#include <algorithm>
#include <cmath>
#include "../../include/tiles/coreStorage.hpp"
#include "../../include/tiles/emptyZone.hpp"
#include "../../include/tiles/entryZone.hpp"
#include "../../include/tiles/exitZone.hpp"
#include "../../include/tiles/openZone.hpp"
#include "../../include/tiles/path.hpp"
#include "../../include/map/map.hpp"
#include "../../include/renderer/renderContext.hpp"
#include "../../include/map/iMapSource.hpp"

Map::Map(std::unique_ptr<IMapSource> source, Cores* cores) {
    if (source) source->buildMap(*this, cores);
}

Map::~Map() {}

int Map::getWidth() const { return width; }

int Map::getHeight() const { return height; }

Tile* Map::getTile(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height)
        return nullptr;

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

const std::vector<Tile*>& Map::getEntries() const { return entries; }

const std::vector<Tile*>& Map::getExits() const { if (exits.empty()) return entries; else return exits; }

CoreStorage* Map::getCoreStorage() const { return coreStorage; }

const std::vector<const Tile*> Map::getNeighbors(const Tile* tile) const {
    std::vector<const Tile*> neighbors;
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

void Map::resize(int w, int h) {
    width = w; height = h;
    grid.resize(height);
    for (int y = 0; y < height; ++y) {
        grid[y].resize(width);
        for (int x = 0; x < width; ++x) {
            grid[y][x] = std::make_unique<EmptyZone>(x, y);
        }
    }
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

void Map::render(RenderContext& ctx) const {
    // Render every Tile
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            if (Tile* t = grid[y][x].get())
                t->render(ctx);

    // Compute the number of ghost tiles (on the sides)
    int tilesToAddLeft   = std::ceil(ctx.offset.x / ctx.tileSize);
    int tilesToAddTop    = std::ceil(ctx.offset.y / ctx.tileSize);
    int tilesToAddRight  = std::ceil((ctx.window.getSize().x - (width * ctx.tileSize + ctx.offset.x)) / ctx.tileSize);
    int tilesToAddBottom = std::ceil((ctx.window.getSize().y - (height * ctx.tileSize + ctx.offset.y)) / ctx.tileSize);

    EmptyZone tempEmpty(0, 0); // Temporary instance

    // Top and bottom
    for (int x = -tilesToAddLeft; x < width + tilesToAddRight; ++x) {
        for (int y = -tilesToAddTop; y < 0; ++y) {
            tempEmpty.setCoords(x, y);
            tempEmpty.render(ctx);
        }
        for (int y = height; y < height + tilesToAddBottom; ++y) {
            tempEmpty.setCoords(x, y);
            tempEmpty.render(ctx);
        }
    }

    // Left and right
    for (int y = 0; y < height; ++y) {
        for (int x = -tilesToAddLeft; x < 0; ++x) {
            tempEmpty.setCoords(x, y);
            tempEmpty.render(ctx);
        }
        for (int x = width; x < width + tilesToAddRight; ++x) {
            tempEmpty.setCoords(x, y);
            tempEmpty.render(ctx);
        }
    }
}
