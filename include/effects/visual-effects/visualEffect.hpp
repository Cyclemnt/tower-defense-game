#ifndef VISUAL_EFFECT_HPP
#define VISUAL_EFFECT_HPP

#include <SFML/Graphics.hpp>
class RenderContext;

/**
 * @class VisualEffect
 * @brief Abstract base class for all transient visual effects.
 *
 * Visual effects are non-interactive entities (e.g., tracer lines,
 * explosions, lasers, or particles) used to enhance the visual feedback
 * of combat and gameplay events.
 *
 * Each effect has a short lifespan and deletes itself once expired.
 */
class VisualEffect {
private:
    bool alive = true; ///< Whether the effect is still active.

public:
    virtual ~VisualEffect() = default;

    /// @brief Advances the effect's internal state.
    /// @param deltaTime Time elapsed since the last frame.
    virtual void update(float deltaTime) = 0;

    /// @brief Renders the effect on screen.
    /// @param ctx The shared render context.
    virtual void render(const RenderContext& ctx) = 0;

    /// @return True if the effect is still active.
    [[nodiscard]] bool isAlive() const noexcept { return alive; }

    /// @brief Marks the effect as dead (ready for cleanup).
    void die() noexcept { alive = false; }
};

#endif // VISUAL_EFFECT_HPP
