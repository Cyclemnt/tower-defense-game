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
    int safe;       ///< Number of cores safe in the base
    int stolen;     ///< Number of cores currently carried by enemies
    int lost;       ///< Number of cores permanently lost

public:
    Cores(int initial = 24);
    ~Cores();

    int getSafe() const;
    int getStolen() const;
    int getLost() const;
    
    /// @brief Enemy steals cores from the base.
    /// @param n Number of cores attempted to be stolen.
    /// @return Number of cores actually stolen (limited by what is available).
    int stealCore(int n);

    /// @brief Cores return to the base (enemy killed while carrying them).
    /// @param n Number of cores returning.
    void returnCore(int n);

    /// @brief Enemy exits the map with cores.
    /// @param n Number of cores permanently lost.
    void loseCore(int n);
};

#endif // CORES_HPP
