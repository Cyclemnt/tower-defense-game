#ifndef CORE_STORAGE_HPP
#define CORE_STORAGE_HPP

#include <string>
#include "tile.hpp"
class Cores;

/**
 * @class CoreStorage
 * @brief Represents the core storage location on the map.
 *
 * CoreStorage tiles contain the cores that creatures attempt to steal.
 * Losing all cores results in the player's defeat.
 */
class CoreStorage : public Tile {
private:
    Cores* cores; ///< Pointer to the cores of the game, to take/deposit.

public:
    /// @brief Constructs a new CoreStorage at the specified coordinates with an initial core count.
    /// @param x The x-coordinate (column) of the core storage.
    /// @param y The y-coordinate (row) of the core storage.
    /// @param coresptr A pointer to the Game's cores.
    CoreStorage(int x, int y, Cores* coresptr);

    /// @brief Destroys the CoreStorage object.
    ~CoreStorage() override = default;

    /// @brief Determines if the core storage is walkable by creatures.
    /// @return true, as core storage areas are walkable.
    bool isWalkable() const override;

    /// @brief Determines if the core storage is buildable.
    /// @return false, as core storage areas are not buildable.
    bool isBuildable() const override;

    /// @brief Retrieves the name/type of this tile.
    /// @return A string representing the type of this tile ("CoreStorage").
    std::string getTypeName() const override;

    /// @brief Returns the current number of cores stored on this tile.
    /// @return The number of cores in storage.
    int getCoreCount() const;

    /// @brief Attempts to take a specified number of cores from the Game's cores.
    /// @param requested The number of cores to try and take.
    /// @return The actual number of cores taken (0 to requested).
    int takeCores(int requested);

    /// @brief Deposits a specified number of cores back into the Game's cores.
    /// @param n The number of cores to deposit.
    void depositCores(int n);
};

#endif // CORE_STORAGE_HPP
