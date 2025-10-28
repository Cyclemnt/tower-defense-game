#ifndef CORES_HPP
#define CORES_HPP

#include <algorithm>

/**
 * @class Cores
 * @brief Tracks the state of cores in the game.
 *
 * Cores represent the central objective the player must protect.
 * They exist in three states:
 * - **Safe**: still in the base.
 * - **Stolen**: currently carried by enemies.
 * - **Lost**: permanently lost when an enemy escapes with them.
 */
class Cores {
private:
    unsigned int safe   = 0; ///< Number of cores safe in the base.
    unsigned int stolen = 0; ///< Number of cores currently carried by enemies.
    unsigned int lost   = 0; ///< Number of cores permanently lost.

public:
    /// @brief Constructs a new Cores tracker.
    /// @param initial Number of cores initially stored safely in the base.
    explicit Cores(unsigned int initial = 24u) noexcept;

    /// @brief Default destructor.
    ~Cores() = default;

    // --- Getters ---
    [[nodiscard]] unsigned int getSafe()   const noexcept { return safe; }
    [[nodiscard]] unsigned int getStolen() const noexcept { return stolen; }
    [[nodiscard]] unsigned int getLost()   const noexcept { return lost; }

    // --- Core logic ---
    /// @brief Attempts to steal a given number of cores.
    /// @param n Number of cores requested.
    /// @return Number of cores actually stolen (limited by availability).
    unsigned int stealCore(unsigned int n) noexcept;

    /// @brief Returns stolen cores to the base (enemy killed before escaping).
    /// @param n Number of cores recovered.
    void returnCore(unsigned int n) noexcept;

    /// @brief Marks cores as permanently lost (enemy escaped).
    /// @param n Number of cores lost.
    void loseCore(unsigned int n) noexcept;
};

#endif // CORES_HPP
