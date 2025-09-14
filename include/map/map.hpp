#ifndef MAP_HPP
#define MAP_HPP

#include "tile.hpp"

#include "coreStorage.hpp"
#include "emptyZone.hpp"
#include "entryZone.hpp"
#include "exitZone.hpp"
#include "openZone.hpp"
#include "path.hpp"

#include "../creatures/creature.hpp"

#include <array>
#include <vector>
#include <memory>

class Map {
private:
    // 2D map
    int width;
    int height;
    std::vector<std::vector<std::unique_ptr<Tile>>> grid;

    // Interest points for the creatures
    std::vector<EntryZone*> entries;
    std::vector<ExitZone*> exits;
    CoreStorage* coreStorage;
    
public:
    Map(int w, int h);
    ~Map();

    // Return map dimensions
    int getWidth() const;
    int getHeight() const;

    // Return pointer to the (x, y) tile
    Tile* getTile(int x, int y) const;

    // Return interest points
    const std::vector<EntryZone*>& getEntries() const;
    const std::vector<ExitZone*>& getExits() const;
    const CoreStorage* getCoreStorage() const;

    // Return neighbors of a tile
    std::vector<Tile*> getNeighbors(Tile* tile) const;
    // Return a path
    std::vector<Tile*> findPath(Creature* c) const;

    // Console debug
    void printMap() const;
};

#endif // MAP_HPP
