#ifndef LASER_EFFECT_HPP
#define LASER_EFFECT_HPP

#include <SFML/Graphics.hpp>
#include "visualEffect.hpp"

class RenderContext;

/**
 * @class LaserEffect
 * @brief Represents a short-lived laser beam between a tower and its target.
 *
 * The laser is composed of two layered rectangles (glow + beam),
 * creating a bright flash effect for energy-based weapons.
 */
class LaserEffect final : public VisualEffect {
private:
    sf::Vector2f start; ///< Start position (in tile coordinates)
    sf::Vector2f end;   ///< End position (in tile coordinates)
    sf::Color color = {255, 120, 30}; ///< Core laser color
    float lifetime = 0.02f; ///< Duration in seconds
    float age = 0.0f;       ///< Current lifetime progress

public:
    /// @brief Constructs a new LaserEffect.
    /// @param start_ Start position (in tiles)
    /// @param end_ End position (in tiles)
    LaserEffect(sf::Vector2f start_, sf::Vector2f end_);

    /// @brief Updates the laser’s lifespan.
    void update(float dt) override;

    /// @brief Draws the laser beam.
    void render(const RenderContext& ctx) override;
};

#endif // LASER_EFFECT_HPP
