#ifndef EXIT_ZONE_HPP
#define EXIT_ZONE_HPP

#include "tile.hpp"

/**
 * @class ExitZone
 * @brief Represents a destination tile for enemies.
 *
 * After stealing cores, creatures leave the map via ExitZones.
 */
class ExitZone final : public Tile {
public:
    explicit ExitZone(sf::Vector2i position_) noexcept;
    ~ExitZone() override = default;

    [[nodiscard]] bool isWalkable() const noexcept override { return true; }
    [[nodiscard]] bool isBuildable() const noexcept override { return false; }
    [[nodiscard]] std::string getTextureName() const override { return "tile_exit.png"; }
};

#endif // EXIT_ZONE_HPP
