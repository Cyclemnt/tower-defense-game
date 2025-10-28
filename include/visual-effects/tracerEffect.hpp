#ifndef TRACER_EFFECT_HPP
#define TRACER_EFFECT_HPP

#include <SFML/Graphics.hpp>
#include "visualEffect.hpp"
#include "tracerSplashEffect.hpp"

/**
 * @class TracerEffect
 * @brief Represents a fast-moving tracer line when a tower fires a bullet.
 *
 * A short-lived colored beam that connects a tower and its target,
 * followed by a small particle splash at the impact point.
 */
class TracerEffect final : public VisualEffect {
private:
    sf::Vector2f start, end; ///< Start and end positions (in tiles)
    sf::Color color;         ///< Tracer color
    float lifetime = 0.6f;   ///< Duration in seconds
    float age = 0.0f;        ///< Current lifetime progress
    float jitterX = 0.0f, jitterY = 0.0f;
    TracerSplashEffect splash; ///< Secondary particle splash

    /// @return A random color between yellow and orange.
    [[nodiscard]] sf::Color generateRandomColor() const;

public:
    /// @brief Constructs a new TracerEffect.
    /// @param start_ Start position (in tiles)
    /// @param end_ End position (in tiles)
    TracerEffect(sf::Vector2f start_, sf::Vector2f end_);

    /// @brief Updates the tracer lifespan.
    void update(float deltaTime) override;

    /// @brief Draws the tracer.
    void render(const RenderContext& ctx) override;
};

#endif // TRACER_EFFECT_HPP
