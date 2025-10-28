#ifndef PATH_HPP
#define PATH_HPP

#include "tile.hpp"

/**
 * @class Path
 * @brief Represents a walkable route for enemies.
 *
 * Path tiles define the roads used by creatures from entries to exits.
 */
class Path final : public Tile {
public:
    explicit Path(sf::Vector2i position_) noexcept;
    ~Path() override = default;

    [[nodiscard]] bool isWalkable() const noexcept override { return true; }
    [[nodiscard]] bool isBuildable() const noexcept override { return false; }
    [[nodiscard]] std::string getTextureName() const override { return "tile_path.png"; }
};

#endif // PATH_HPP
