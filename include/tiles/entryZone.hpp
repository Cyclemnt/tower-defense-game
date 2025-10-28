#ifndef ENTRY_ZONE_HPP
#define ENTRY_ZONE_HPP

#include "tile.hpp"

/**
 * @class EntryZone
 * @brief Represents an enemy spawn tile.
 *
 * Creatures enter the map through EntryZone tiles.
 */
class EntryZone final : public Tile {
public:
    explicit EntryZone(sf::Vector2i position_) noexcept;
    ~EntryZone() override = default;

    [[nodiscard]] bool isWalkable() const noexcept override { return true; }
    [[nodiscard]] bool isBuildable() const noexcept override { return false; }
    [[nodiscard]] std::string getTextureName() const override { return "tile_entry.png"; }
};

#endif // ENTRY_ZONE_HPP
