#ifndef PATH_HPP
#define PATH_HPP

#include "tile.hpp"

/// @brief Represents a path tile on the map, which is walkable and not buildable.
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
    std::string getTypeName() const override;
};

#endif // PATH_HPP
