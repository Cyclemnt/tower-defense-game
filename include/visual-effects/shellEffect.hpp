#ifndef SHELL_EFFECT_HPP
#define SHELL_EFFECT_HPP

#include <SFML/Graphics.hpp>
#include "visualEffect.hpp"

class RenderContext;

/**
 * @class ShellEffect
 * @brief Simulates a projectile (shell) traveling toward a target.
 *
 * The projectile moves linearly toward its target and disappears on impact
 * or when its lifetime expires. Used by the Mortar tower and similar weapons.
 */
class ShellEffect final : public VisualEffect {
private:
    sf::Vector2f position;     ///< Current position (in tiles)
    sf::Vector2f target;  ///< Target position (in tiles)
    float speed;          ///< Travel speed (tiles per second)
    float lifetime = 5.0f; ///< Maximum lifetime (seconds)
    float radius = 0.1f;   ///< Visual size (in tiles)

public:
    /// @brief Constructs a new ShellEffect.
    /// @param start_ Start position (in tiles)
    /// @param end_ Target position (in tiles)
    /// @param speed_ Projectile speed (tiles/sec)
    ShellEffect(sf::Vector2f start_, sf::Vector2f end_, float speed_);

    /// @brief Moves the projectile toward the target.
    void update(float dt) override;

    /// @brief Draws the projectile as a simple circle.
    void render(const RenderContext& ctx) override;

    /// @return Current projectile position.
    [[nodiscard]] sf::Vector2f getPosition() const noexcept { return position; }
};

#endif // SHELL_EFFECT_HPP
