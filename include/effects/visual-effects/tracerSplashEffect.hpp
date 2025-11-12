#ifndef TRACER_SPLASH_EFFECT_HPP
#define TRACER_SPLASH_EFFECT_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "visualEffect.hpp"

/**
 * @class TracerSplashEffect
 * @brief Small particle burst at the end of a tracer beam.
 */
class TracerSplashEffect final : public VisualEffect {
public:
    /// @brief Simple structure to describe a particule
    struct SimpleParticle {
        sf::Vector2f v;
        float speed;
        float radius;
        float age = 0.0f; ///< Current lifetime progress
        float lifetime; ///< Duration in seconds
    };

private:
    sf::Vector2f position; ///< Position (in tile coordinates)
    sf::Color color;       ///< Particles color
    std::vector<SimpleParticle> particles; ///< List of particles
    float age = 0.0f;      ///< Current lifetime progress
    float lifetime = 0.6f; ///< Duration in seconds

public:
    /// @brief Constructs a new TracerSplashEffect.
    /// @param start_ Start position (in tiles)
    /// @param end_ End position (in tiles)
    /// @param color_ Color
    TracerSplashEffect(sf::Vector2f position_, sf::Color color_);

    /// @brief Updates the splash's lifespan.
    void update(float dt) override;

    /// @brief Draws the tracer's splash.
    void render(const RenderContext& ctx) override;
};

#endif // TRACER_SPLASH_EFFECT_HPP
