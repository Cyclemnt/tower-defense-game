#ifndef TILE_HPP
#define TILE_HPP

#include <string>
#include "../renderer/renderable.hpp"

/**
 * @class Tile
 * @brief Abstract base class for all map tiles.
 *
 * A Tile represents a cell on the game map grid. Each type of tile defines
 * whether it can be walked on by creatures and/or built upon by towers.
 * Derived classes include EmptyZone, Path, OpenZone, EntryZone, ExitZone,
 * and CoreStorage.
 */
class Tile : public IRenderable {
private:
    int x;  ///< The x-coordinate (column) of the tile.
    int y;  ///< The y-coordinate (row) of the tile.

public:
    /// @brief Constructs a new Tile at the specified coordinates.
    /// @param x_ The x-coordinate (column) of the tile.
    /// @param y_ The y-coordinate (row) of the tile.
    Tile(int x_, int y_);

    /// @brief Virtual destructor for the Tile class.
    virtual ~Tile() = default;

    /// @brief Determines if the tile is walkable.
    /// @return true if the tile is walkable, false otherwise.
    virtual bool isWalkable() const = 0;

    /// @brief Determines if the tile is buildable.
    /// @return true if the tile is buildable, false otherwise.
    virtual bool isBuildable() const = 0;

    /// @brief Retrieves the x-coordinate (column) of the tile.
    /// @return The x-coordinate of the tile.
    int getX() const;

    /// @brief Retrieves the y-coordinate (row) of the tile.
    /// @return The y-coordinate of the tile.
    int getY() const;

    /// @brief Retrieves the name/type of the tile.
    /// @return A string representing the type of this tile.
    virtual std::string getTextureName() const = 0;

    void render(const RenderContext& ctx) const override;
};

#endif // TILE_HPP
