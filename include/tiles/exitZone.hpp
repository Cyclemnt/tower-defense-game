#ifndef EXIT_ZONE_HPP
#define EXIT_ZONE_HPP

#include <string>
#include "tile.hpp"

/**
 * @class ExitZone
 * @brief Represents a creature exit point.
 *
 * ExitZone tiles are the goal locations that creatures attempt to reach after stealing cores from the base.
 */
class ExitZone : public Tile {
public:
    /// @brief Constructs a new ExitZone at the specified coordinates.
    /// @param x The x-coordinate (column) of the exit zone.
    /// @param y The y-coordinate (row) of the exit zone.
    ExitZone(int x, int y);

    /// @brief Destroys the ExitZone object.
    ~ExitZone();

    /// @brief Determines if the exit zone is walkable by creatures.
    /// @return true, as exit zones are walkable.
    bool isWalkable() const override;

    /// @brief Determines if the exit zone is buildable.
    /// @return false, as exit zones cannot be built on.
    bool isBuildable() const override;

    /// @brief Retrieves the name/type of this tile.
    /// @return A string representing the type of this tile ("ExitZone").
    std::string getTextureName() const override;
};

#endif // EXIT_ZONE_HPP
