#ifndef MAP_HPP
#define MAP_HPP

#include "tile.hpp"
#include "entryZone.hpp"
#include "coresSafe.hpp"
#include "exitZone.hpp"
#include "../creatures/creature.hpp"
#include <array>
#include <vector>

class Map {
private:
    // 2D map
    std::array<std::array<Tile*, 16>, 16> map;
    int width;
    int height;

    // Interest points for the creatures
    std::vector<EntryZone*> entries;
    CoresSafe* coressafe;
    std::vector<ExitZone*> exits;
    
public:
    Map(/* args */);
    ~Map();

    void getTile(int x, int y) const;
    void getNeighbors(Tile*) const;
    std::vector<Tile*> findPath(Creature* c) const;
};

#endif // MAP_HPP
