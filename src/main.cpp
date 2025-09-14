#include "../include/game.hpp"

#include "../include/map/map.hpp"
#include "../include/pathfinder.hpp"

#include <iostream>

int main() {
    Map map(5, 5);

    // Create a wall (To test a*)
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            map.placeTile(std::make_unique<Path>(i, j));
    map.placeTile(std::make_unique<EmptyZone>(1, 3));
    map.placeTile(std::make_unique<EmptyZone>(2, 3));
    map.placeTile(std::make_unique<EmptyZone>(3, 3));
    map.placeTile(std::make_unique<EmptyZone>(3, 2));
    map.placeTile(std::make_unique<EmptyZone>(3, 1));
    map.placeTile(std::make_unique<EmptyZone>(3, 0));
    
    // Interest points setup
    map.placeTile(std::make_unique<EntryZone>(0, 0));
    map.placeTile(std::make_unique<ExitZone>(4, 4));
    map.placeTile(std::make_unique<CoreStorage>(2, 2, 24));

    map.printMap();

    Pathfinder pf(map);
    std::vector<Tile*> path = pf.findPath(map.getEntries()[0], map.getExits()[0]);

    for (Tile* t : path) {
        std::cout << "(" << t->getX() << "," << t->getY() << ") ";
    }
    
    return 0;
}
