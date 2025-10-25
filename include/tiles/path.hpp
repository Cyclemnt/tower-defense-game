#ifndef PATH_HPP
#define PATH_HPP

#include <string>
#include "tile.hpp"

/**
 * @class Path
 * @brief Represents a walkable tile on the map.
 *
 * Path tiles define the routes creatures can follow from entry points
 * to the core storage and eventually to exit points.
 */
class Path : public Tile {
public:
    /// @brief Constructs a new Path at the specified coordinates.
    /// @param x The x-coordinate (column) of the path.
    /// @param y The y-coordinate (row) of the path.
    Path(int x, int y);

    /// @brief Destroys the Path object.
    ~Path();

    /// @brief Determines if the path is walkable by creatures.
    /// @return true, as paths are walkable.
    bool isWalkable() const override;

    /// @brief Determines if the path is buildable.
    /// @return false, as paths cannot be built on.
    bool isBuildable() const override;

    /// @brief Retrieves the name/type of this tile.
    /// @return A string representing the type of this tile ("Path").
    std::string getTextureName() const override;
};

#endif // PATH_HPP
