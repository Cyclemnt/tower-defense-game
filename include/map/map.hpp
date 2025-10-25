#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <memory>
class IMapSource;
class Cores;
class Tile;
class CoreStorage;
class RenderContext;

/**
 * @class Map
 * @brief Represents the game map grid.
 *
 * The Map manages a 2D grid of Tile objects, provides access to neighbors
 * for pathfinding, and keeps track of key points such as entries, exits,
 * and the core storage.
 */
class Map {
private:
    int width = 0;  ///< The width of the map (number of columns).
    int height = 0; ///< The height of the map (number of rows).

    /// @brief 2D grid representing the map's layout, with each cell containing a unique tile.
    std::vector<std::vector<std::unique_ptr<Tile>>> grid;

    /// @brief List of entry zones (special areas where creatures can enter).
    std::vector<Tile*> entries;

    /// @brief List of exit zones (special areas where creatures can exit).
    std::vector<Tile*> exits;

    /// @brief Pointer to the core storage object (special area where cores are stored).
    CoreStorage* coreStorage;
    
public:
    /// @brief Constructs a new map.
    Map(std::unique_ptr<IMapSource> source, Cores* cores = nullptr);

    /// @brief Destroys the map object and frees any allocated resources.
    ~Map();

    /// @brief Returns the width of the map (number of columns).
    /// @return The width of the map.
    int getWidth() const;

    /// @brief Returns the height of the map (number of rows).
    /// @return The height of the map.
    int getHeight() const;

    /// @brief Retrieves the tile located at the given coordinates.
    /// @param x The x-coordinate (column) of the tile.
    /// @param y The y-coordinate (row) of the tile.
    /// @return A pointer to the tile located at the specified coordinates.
    /// @throws std::out_of_range If the provided coordinates are outside the map's bounds.
    Tile* getTile(int x, int y) const;

    /// @brief Places a new tile at the correct position on the grid.
    /// @param tile A unique pointer to the tile object to be placed on the map.
    void placeTile(std::unique_ptr<Tile> tile);

    /// @brief Returns a reference to the list of entry zones on the map.
    /// @return A constant reference to the vector of EntryZone pointers.
    const std::vector<Tile*>& getEntries() const;

    /// @brief Returns a reference to the list of exit zones on the map.
    /// @return A constant reference to the vector of ExitZone pointers.
    const std::vector<Tile*>& getExits() const;

    /// @brief Returns a pointer to the core storage of the map.
    /// @return A pointer to the CoreStorage object.
    CoreStorage* getCoreStorage() const;

    /// @brief Returns a list of neighboring tiles surrounding the given tile.
    /// @param tile The central tile to check neighbors for.
    /// @return A vector of pointers to neighboring tiles (adjacent horizontally or vertically).
    std::vector<Tile*> getNeighbors(Tile* tile) const;

    /// @brief Changes the dimention of the map.
    /// @param w The width of the map (number of columns).
    /// @param h The height of the map (number of rows).
    void resize(int w, int h);

    /// @brief Prints the current map to the console for debugging purposes.
    /// @details This method outputs a visual representation of the map, 
    /// where different types of tiles are displayed using specific characters.
    void printMap() const;

    // Map.hpp
    void render(RenderContext& ctx) const;
};

#endif // MAP_HPP
