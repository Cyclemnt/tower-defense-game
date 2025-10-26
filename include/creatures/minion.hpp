#ifndef MINION_HPP
#define MINION_HPP

#include "creature.hpp"

/**
 * @class Minion
 * @brief A light and fast enemy type.
 *
 * The Minion is a weak but agile enemy unit. It moves quickly and is often spawned
 * in large groups to overwhelm defenses by sheer numbers.
 * 
 * Boosted variants have increased health and rewards.
 */
class Minion final : public Creature {
public:
    /**
     * @brief Constructs a Minion.
     * @param boosted_ Whether this Minion is a boosted variant.
     */
    explicit Minion(bool boosted_ = false) noexcept;

    /// @brief Virtual destructor.
    ~Minion() override = default;

protected:
    /// @brief Returns the texture name for this creature.
    /// @param frame The animation frame index.
    [[nodiscard]] std::string getTextureName(int frame) const override;
};

#endif // MINION_HPP
