#include <iostream>
#include <algorithm>
#include <cmath>
#include "../../include/map/map.hpp"
#include "../../include/map/iMapSource.hpp"
#include "../../include/tiles/coreStorage.hpp"
#include "../../include/tiles/entryZone.hpp"
#include "../../include/tiles/exitZone.hpp"
#include "../../include/tiles/openZone.hpp"
#include "../../include/tiles/emptyZone.hpp"
#include "../../include/tiles/path.hpp"
#include "../../include/renderer/renderContext.hpp"

Map::Map(std::unique_ptr<IMapSource> source, Cores* cores) {
    if (source) source->buildMap(*this, cores);
}

Map::~Map() = default;

Tile* Map::getTile(const sf::Vector2i& pos) const noexcept {
    if (pos.x < 0 || pos.y < 0 || pos.x >= static_cast<int>(size.x) || pos.y >= static_cast<int>(size.y))
        return nullptr;
    return grid[pos.y][pos.x].get();
}

const std::vector<Tile*>& Map::getExits() const noexcept {
    return exits.empty() ? entries : exits;
}

std::vector<const Tile*> Map::getNeighbors(const Tile* tile) const noexcept {
    std::vector<const Tile*> neighbors;
    const sf::Vector2i pos = tile->getPosition();

    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};

    for (int i = 0; i < 4; ++i) {
        const int nx = pos.x + dx[i];
        const int ny = pos.y + dy[i];
        if (nx >= 0 && ny >= 0 && nx < static_cast<int>(size.x) && ny < static_cast<int>(size.y))
            neighbors.push_back(grid[ny][nx].get());
    }
    return neighbors;
}

void Map::resize(unsigned int w, unsigned int h) {
    size = {w, h};
    grid.resize(h);
    for (auto& row : grid) {
        row.clear();
        row.reserve(w);
        for (unsigned int x = 0; x < w; ++x)
            row.push_back(std::make_unique<EmptyZone>(sf::Vector2i(x, static_cast<int>(&row - &grid[0]))));
    }
}

void Map::placeTile(std::unique_ptr<Tile> tile) {
    const sf::Vector2i pos = tile->getPosition();
    if (pos.x < 0 || pos.y < 0 || pos.x >= static_cast<int>(size.x) || pos.y >= static_cast<int>(size.y))
        return;

    // Remove previous tile type references
    if (auto old = grid[pos.y][pos.x].get()) {
        if (auto e = dynamic_cast<EntryZone*>(old))
            entries.erase(std::remove(entries.begin(), entries.end(), e), entries.end());
        else if (auto ex = dynamic_cast<ExitZone*>(old))
            exits.erase(std::remove(exits.begin(), exits.end(), ex), exits.end());
        else if (dynamic_cast<CoreStorage*>(old))
            coreStorage = nullptr;
    }

    grid[pos.y][pos.x] = std::move(tile);
    Tile* t = grid[pos.y][pos.x].get();

    // Add new references
    if (auto e = dynamic_cast<EntryZone*>(t))
        entries.push_back(e);
    else if (auto ex = dynamic_cast<ExitZone*>(t))
        exits.push_back(ex);
    else if (auto c = dynamic_cast<CoreStorage*>(t))
        coreStorage = c;
}

void Map::printMap() const {
    for (unsigned int y = 0; y < size.y; ++y) {
        for (unsigned int x = 0; x < size.x; ++x) {
            const Tile* t = grid[y][x].get();
            char symbol = '.';
            if (dynamic_cast<const Path*>(t)) symbol = '#';
            else if (dynamic_cast<const OpenZone*>(t)) symbol = 'O';
            else if (dynamic_cast<const EntryZone*>(t)) symbol = 'E';
            else if (dynamic_cast<const ExitZone*>(t)) symbol = 'X';
            else if (dynamic_cast<const CoreStorage*>(t)) symbol = 'C';
            std::cout << symbol << ' ';
        }
        std::cout << '\n';
    }
}

void Map::render(const RenderContext& ctx) const {
    // Draw all tiles
    for (unsigned int y = 0; y < size.y; ++y)
        for (unsigned int x = 0; x < size.x; ++x)
            if (Tile* t = grid[y][x].get())
                t->render(ctx);

    // Compute filler around edges (empty tiles beyond visible area)
    const int tilesLeft   = std::ceil(ctx.offset.x / ctx.tileSize);
    const int tilesTop    = std::ceil(ctx.offset.y / ctx.tileSize);
    const int tilesRight  = std::ceil((ctx.window.getSize().x - (size.x * ctx.tileSize + ctx.offset.x)) / ctx.tileSize);
    const int tilesBottom = std::ceil((ctx.window.getSize().y - (size.y * ctx.tileSize + ctx.offset.y)) / ctx.tileSize);

    // Top and bottom
    for (int x = -tilesLeft; x < static_cast<int>(size.x) + tilesRight; ++x) {
        for (int y = -tilesTop; y < 0; ++y) {
            EmptyZone tempEmpty({x, y});
            tempEmpty.render(ctx);
        }
        for (int y = static_cast<int>(size.y); y < static_cast<int>(size.y) + tilesBottom; ++y) {
            EmptyZone tempEmpty({x, y});
            tempEmpty.render(ctx);
        }
    }

    // Left and right
    for (int y = 0; y < static_cast<int>(size.y); ++y) {
        for (int x = -tilesLeft; x < 0; ++x) {
            EmptyZone tempEmpty({x, y});
            tempEmpty.render(ctx);
        }
        for (int x = static_cast<int>(size.x); x < static_cast<int>(size.x) + tilesRight; ++x) {
            EmptyZone tempEmpty({x, y});
            tempEmpty.render(ctx);
        }
    }
}
