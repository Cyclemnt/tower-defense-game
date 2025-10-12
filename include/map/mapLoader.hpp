#ifndef MAP_LOADER_HPP
#define MAP_LOADER_HPP

#include <string>
class Map;
class Cores;

class MapLoader {
public:
    static void loadFromFile(Map& map, const std::string& path, Cores* cores = nullptr);
};

#endif // MAP_LOADER_HPP
