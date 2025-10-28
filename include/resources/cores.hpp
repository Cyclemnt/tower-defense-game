#ifndef CORES_HPP
#define CORES_HPP

/**
 * @class Cores
 * @brief Tracks the state of cores in the game.
 *
 * Cores represent the objectives the player must defend.
 * They can be in three states:
 * - safe: still in the base
 * - stolen: currently carried by enemies
 * - lost: permanently lost after an enemy exits the map
 */
class Cores {
private:
    unsigned int safe = 0;       ///< Number of cores safe in the base
    unsigned int stolen = 0;     ///< Number of cores currently carried by enemies
    unsigned int lost = 0;       ///< Number of cores permanently lost

public:
    Cores(unsigned int initial = 24u);
    ~Cores();

    unsigned int getSafe() const { return safe; }
    unsigned int getStolen() const { return stolen; }
    unsigned int getLost() const { return lost; }
    
    /// @brief Enemy steals cores from the base.
    /// @param n Number of cores attempted to be stolen.
    /// @return Number of cores actually stolen (limited by what is available).
    unsigned int stealCore(unsigned int n);

    /// @brief Cores return to the base (enemy killed while carrying them).
    /// @param n Number of cores returning.
    void returnCore(unsigned int n);

    /// @brief Enemy exits the map with cores.
    /// @param n Number of cores permanently lost.
    void loseCore(unsigned int n);
};

#endif // CORES_HPP
