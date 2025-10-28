#ifndef CORE_STORAGE_HPP
#define CORE_STORAGE_HPP

#include <string>
#include <SFML/System.hpp>
#include "tile.hpp"

class Cores;
class RenderContext;

/**
 * @class CoreStorage
 * @brief Special tile representing the player's core repository.
 *
 * The CoreStorage is where creatures attempt to steal cores. Losing all cores
 * results in the player’s defeat.
 */
class CoreStorage final : public Tile {
private:
    Cores* cores = nullptr; ///< Pointer to the global core manager.

public:
    /// @brief Constructs a CoreStorage tile.
    /// @param position_ Position in the grid.
    /// @param coresPtr Pointer to the core storage manager.
    explicit CoreStorage(sf::Vector2i position_, Cores* coresPtr) noexcept;

    ~CoreStorage() override = default;

    [[nodiscard]] bool isWalkable() const noexcept override { return true; }
    [[nodiscard]] bool isBuildable() const noexcept override { return false; }
    [[nodiscard]] std::string getTextureName() const override { return "tile_core.png"; }

    /// @brief Attempts to steal a given number of cores.
    /// @param requested Number of cores to steal.
    /// @return Actual number of cores stolen.
    unsigned int takeCores(unsigned int requested) const noexcept;

    void render(const RenderContext& ctx) const override;
};

#endif // CORE_STORAGE_HPP
