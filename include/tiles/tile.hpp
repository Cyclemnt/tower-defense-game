#ifndef TILE_HPP
#define TILE_HPP

#include <string>
#include <SFML/System.hpp>
class RenderContext;

/**
 * @class Tile
 * @brief Abstract base class for all map tiles.
 *
 * A Tile represents a cell on the game map grid. Each type of tile defines
 * whether it can be walked on by creatures and/or built upon by towers.
 * Derived classes include EmptyZone, Path, OpenZone, EntryZone, ExitZone,
 * and CoreStorage.
 */
class Tile {
protected:
    const sf::Vector2i position; ///< The coordinates of the tile.

public:
    /// @brief Constructs a new Tile at the specified coordinates.
    /// @param position_ The coordinates of the tile.
    Tile(sf::Vector2i position_ = {0, 0});

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
    sf::Vector2i getPosition() const { return position; }

    /// @brief Retrieves the name/type of the tile.
    /// @return A string representing the type of this tile.
    virtual std::string getTextureName() const = 0;
    virtual void render(const RenderContext& ctx) const;
};

#endif // TILE_HPP
