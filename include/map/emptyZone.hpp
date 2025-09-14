#ifndef EMPTY_ZONE_HPP
#define EMPTY_ZONE_HPP

#include "tile.hpp"

/// @brief Represents an empty zone on the map, which is not walkable nor buildable.
class EmptyZone : public Tile {
public:
    /// @brief Constructs a new EmptyZone at the specified coordinates.
    /// @param x The x-coordinate (column) of the zone.
    /// @param y The y-coordinate (row) of the zone.
    EmptyZone(int x, int y);

    /// @brief Destroys the EmptyZone object.
    ~EmptyZone();

    /// @brief Determines if the zone is walkable by creatures.
    /// @return false, as an empty zone is not walkable.
    bool isWalkable() const override;

    /// @brief Determines if the zone is buildable (i.e., can a structure be placed on it).
    /// @return false, as empty zones cannot be built on.
    bool isBuildable() const override;

    /// @brief Retrieves the name/type of this tile.
    /// @return A string representing the type of this tile ("EmptyZone").
    std::string getTypeName() const override;
};

#endif // EMPTY_ZONE_HPP
