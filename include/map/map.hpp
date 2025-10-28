#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <memory>
#include <SFML/System.hpp>

class IMapSource;
class Cores;
class Tile;
class CoreStorage;
class RenderContext;

/**
 * @class Map
 * @brief Represents the game world grid made of Tiles.
 *
 * The Map owns all Tile instances, provides access to entries, exits, and
 * the CoreStorage, and supports spatial queries and rendering.
 */
class Map {
private:
    sf::Vector2u size {0, 0}; ///< Width and height in tiles.
    std::vector<std::vector<std::unique_ptr<Tile>>> grid; ///< 2D grid of tiles.
    std::vector<Tile*> entries; ///< Entry points for enemies.
    std::vector<Tile*> exits;   ///< Exit points for enemies.
    CoreStorage* coreStorage = nullptr; ///< Pointer to the core storage tile.

public:
    /// @brief Constructs the map using a map source (text, procedural, etc.).
    explicit Map(std::unique_ptr<IMapSource> source, Cores* cores = nullptr);

    /// @brief Destroys the map and all contained tiles.
    ~Map();

    // --- Accessors ---
    [[nodiscard]] const sf::Vector2u& getSize() const noexcept { return size; }
    [[nodiscard]] Tile* getTile(const sf::Vector2i& pos) const noexcept;
    [[nodiscard]] const std::vector<Tile*>& getEntries() const noexcept { return entries; }
    [[nodiscard]] const std::vector<Tile*>& getExits() const noexcept;
    [[nodiscard]] const CoreStorage* getCoreStorage() const noexcept { return coreStorage; }

    // --- Grid management ---
    void resize(unsigned int width, unsigned int height);
    void placeTile(std::unique_ptr<Tile> tile);
    [[nodiscard]] std::vector<const Tile*> getNeighbors(const Tile* tile) const noexcept;

    // --- Debug & rendering ---
    void printMap() const;
    void render(const RenderContext& ctx) const;
};

#endif // MAP_HPP
