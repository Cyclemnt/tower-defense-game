#ifndef ENTRY_ZONE_HPP
#define ENTRY_ZONE_HPP

#include "tile.hpp"

/// @brief Represents an entry zone on the map, where creatures can enter.
class EntryZone : public Tile {
public:
    /// @brief Constructs a new EntryZone at the specified coordinates.
    /// @param x The x-coordinate (column) of the entry zone.
    /// @param y The y-coordinate (row) of the entry zone.
    EntryZone(int x, int y);

    /// @brief Destroys the EntryZone object.
    ~EntryZone();

    /// @brief Determines if the entry zone is walkable by creatures.
    /// @return true, as entry zones are walkable.
    bool isWalkable() const override;

    /// @brief Determines if the entry zone is buildable.
    /// @return false, as entry zones cannot be built on.
    bool isBuildable() const override;

    /// @brief Retrieves the name/type of this tile.
    /// @return A string representing the type of this tile ("EntryZone").
    std::string getTypeName() const override;
};

#endif // ENTRY_ZONE_HPP
