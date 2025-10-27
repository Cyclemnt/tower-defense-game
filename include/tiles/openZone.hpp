#ifndef OPEN_ZONE_HPP
#define OPEN_ZONE_HPP

#include <string>
#include <SFML/System.hpp>
#include "tile.hpp"

/**
 * @class OpenZone
 * @brief Represents a buildable tile on the map.
 *
 * OpenZone tiles allow the player to place towers. They are not walkable
 * for creatures and may be marked as occupied once a tower is built.
 */
class OpenZone : public Tile {
private:
    bool occupied; ///< Indicates if the zone is currently occupied by a tower.

public:
    /// @brief Constructs a new OpenZone at the specified coordinates.
    /// @param x The x-coordinate (column) of the open zone.
    /// @param y The y-coordinate (row) of the open zone.
    OpenZone(sf::Vector2i position_);

    /// @brief Destroys the OpenZone object.
    ~OpenZone();

    /// @brief Determines if the open zone is walkable by creatures.
    /// @return true if the zone is not occupied, false otherwise.
    bool isWalkable() const override;

    /// @brief Determines if the open zone is buildable.
    /// @return true if the zone is not occupied, false otherwise.
    bool isBuildable() const override;

    /// @brief Retrieves the name/type of this tile.
    /// @return A string representing the type of this tile ("OpenZone").
    std::string getTextureName() const override;

    /// @brief Checks if the open zone is currently occupied.
    /// @return true if the zone is occupied, false otherwise.
    bool isOccupied() const;

    /// @brief Sets the occupation status of the open zone.
    /// @param value The occupation status to set (true for occupied, false for not).
    void setOccupied(bool value);
};

#endif // OPEN_ZONE_HPP
