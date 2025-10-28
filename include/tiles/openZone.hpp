#ifndef OPEN_ZONE_HPP
#define OPEN_ZONE_HPP

#include "tile.hpp"

/**
 * @class OpenZone
 * @brief Represents a buildable area for player towers.
 *
 * OpenZone tiles can host a tower, and are not walkable by creatures.
 */
class OpenZone final : public Tile {
private:
    bool occupied = false; ///< Whether the tile currently hosts a tower.

public:
    explicit OpenZone(sf::Vector2i position_) noexcept;
    ~OpenZone() override = default;

    [[nodiscard]] bool isWalkable() const noexcept override { return !occupied; }
    [[nodiscard]] bool isBuildable() const noexcept override { return true; }
    [[nodiscard]] std::string getTextureName() const override { return "tile_open.png"; }

    [[nodiscard]] bool isOccupied() const noexcept { return occupied; }
    void setOccupied(bool value) noexcept { occupied = value; }
};

#endif // OPEN_ZONE_HPP
