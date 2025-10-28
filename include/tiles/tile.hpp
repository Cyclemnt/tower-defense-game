#ifndef TILE_HPP
#define TILE_HPP

#include <string>
#include <SFML/System.hpp>
class RenderContext;

/**
 * @class Tile
 * @brief Abstract base class for all map tiles.
 *
 * Each Tile represents a cell of the grid. Derived classes
 * define whether the tile can be walked on or built upon.
 */
class Tile {
protected:
    const sf::Vector2i position; ///< Coordinates in grid (x, y).

public:
    explicit Tile(sf::Vector2i position_ = {0, 0}) noexcept;
    virtual ~Tile() = default;

    [[nodiscard]] const sf::Vector2i& getPosition() const noexcept { return position; }

    [[nodiscard]] virtual bool isWalkable() const noexcept = 0;
    [[nodiscard]] virtual bool isBuildable() const noexcept = 0;
    [[nodiscard]] virtual std::string getTextureName() const = 0;

    virtual void render(const RenderContext& ctx) const;
};

#endif // TILE_HPP
