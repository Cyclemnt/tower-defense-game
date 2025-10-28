#ifndef EXPLOSION_EFFECT_HPP
#define EXPLOSION_EFFECT_HPP

#include <SFML/Graphics.hpp>
#include "visualEffect.hpp"

class RenderContext;

/**
 * @class ExplosionEffect
 * @brief Expanding circular explosion effect with fade-out.
 *
 * Used to represent impacts from area-of-effect weapons.
 */
class ExplosionEffect final : public VisualEffect {
private:
    sf::Vector2f position; ///< Center of the explosion (in tiles)
    float age = 0.0f; ///< Current lifetime progress
    float lifetime = 0.3f; ///< Duration in seconds
    float maxRadius; ///< Maximum radius (in tiles)

public:
    /// @brief Constructs a new ExplosionEffect.
    /// @param position_ Explosion center (in tiles)
    /// @param radius Maximum radius (in tiles)
    ExplosionEffect(sf::Vector2f position_, float maxRadius_ = 0.4f);

    /// @brief Updates expansion and fade.
    void update(float dt) override;

    /// @brief Renders the explosion with glow and core layers.
    void render(const RenderContext& ctx) override;
};

#endif // EXPLOSION_EFFECT_HPP
