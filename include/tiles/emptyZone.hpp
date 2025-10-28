#ifndef EMPTY_ZONE_HPP
#define EMPTY_ZONE_HPP

#include <string>
#include "tile.hpp"

/**
 * @class EmptyZone
 * @brief Represents an unused, non-walkable map tile.
 *
 * EmptyZone tiles are visual fillers used outside the playable area
 * or as decorative terrain.
 */
class EmptyZone final : public Tile {
private:
    static constexpr uint32_t kSeed = 0x4470f446u; ///< Randomization seed for texture variation.

    [[nodiscard]] std::string getRandomTextureName() const noexcept;

public:
    explicit EmptyZone(sf::Vector2i position_) noexcept;
    ~EmptyZone() override = default;

    [[nodiscard]] bool isWalkable() const noexcept override { return false; }
    [[nodiscard]] bool isBuildable() const noexcept override { return false; }
    [[nodiscard]] std::string getTextureName() const override { return "tile_empty.png"; }

    void render(const RenderContext& ctx) const override;
};

#endif // EMPTY_ZONE_HPP
