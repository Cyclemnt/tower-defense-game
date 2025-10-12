#ifndef EMPTY_ZONE_HPP
#define EMPTY_ZONE_HPP

#include <string>
#include "tile.hpp"

/**
 * @class EmptyZone
 * @brief Represents an unused tile on the map.
 *
 * EmptyZone tiles are neither walkable by creatures nor buildable by towers.
 */
class EmptyZone : public Tile {
private:
    const uint32_t emptyTileSeed = 0xA1B2C3D5; ///< Seed used for deterministic texture generation
    const std::string getRandomTextureName(int x, int y) const;
public:
    /// @brief Constructs a new EmptyZone at the specified coordinates.
    /// @param x The x-coordinate (column) of the empty zone.
    /// @param y The y-coordinate (row) of the empty zone.
    EmptyZone(int x, int y);

    /// @brief Destroys the EmptyZone object.
    ~EmptyZone();

    /// @brief Determines if the empty zone is walkable by creatures.
    /// @return false, as an empty zone is not walkable.
    bool isWalkable() const override;

    /// @brief Determines if the empty zone is buildable.
    /// @return false, as empty zones cannot be built on.
    bool isBuildable() const override;

    /// @brief Retrieves the name/type of this tile.
    /// @return A string representing the type of this tile ("EmptyZone").
    std::string getTextureName() const override;

    void render(const RenderContext& ctx) const override;
};

#endif // EMPTY_ZONE_HPP
