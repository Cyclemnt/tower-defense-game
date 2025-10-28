#ifndef TOWER_HPP
#define TOWER_HPP

#include <string>
#include <vector>
#include <array>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include "../resources/materials.hpp"

class Creature;
class VisualEffect;
class RenderContext;

/**
 * @class Tower
 * @brief Abstract base class for all towers in the tower defense game.
 *
 * Towers are placed on map tiles and automatically attack nearby enemies.
 * Each tower has attributes such as damage, range, and fire rate, and may
 * produce visual effects when firing. Derived classes specialize behavior
 * (e.g., Gatling, Laser, Mortar).
 */
class Tower {
protected:
    sf::Vector2i position; ///< Map tile coordinates.

    Materials::Quantities cost; ///< Construction cost (Au, Ag, Cu).

    float damage;   ///< Damage per attack.
    float range;    ///< Attack range (in tiles).
    float fireRate; ///< Attacks per second.
    unsigned int level = 1u; ///< Upgrade level (starts at 1).

    float cooldown = 0.0f; ///< Time remaining before next attack (seconds).

    Creature* target = nullptr; ///< Currently locked target.

    std::vector<std::unique_ptr<VisualEffect>> visualEffects; ///< Active visual effects.

public:
    /// @brief Constructs a tower with base stats.
    Tower(sf::Vector2i position_, Materials::Quantities cost_, float damage_, float range_, float fireRate_) noexcept;

    virtual ~Tower() = default;

    /// @brief Updates tower logic every tick.
    /// @param deltaTime Time elapsed since last update.
    /// @param creatures All creatures currently active on the map.
    virtual void update(float deltaTime, const std::vector<std::unique_ptr<Creature>>& creatures);

    /// @brief Attacks a single creature.
    /// @param target Target to hit (must not be null).
    virtual void attack(Creature* target);

    /// @brief Upgrades the tower, increasing damage, range, and fire rate.
    virtual void upgrade();

    /// @brief Renders the tower sprite.
    virtual void render(const RenderContext& ctx) const;

    // --- Getters ---
    [[nodiscard]] const sf::Vector2i& getPosition() const noexcept { return position; }
    [[nodiscard]] int getLevel() const noexcept { return level; }
    [[nodiscard]] float getDamage() const noexcept { return damage; }
    [[nodiscard]] float getRange() const noexcept { return range; }
    [[nodiscard]] float getFireRate() const noexcept { return fireRate; }
    [[nodiscard]] Materials::Quantities getCost() const noexcept { return cost; }
    [[nodiscard]] const Creature* getTarget() const noexcept { return target; }

    /// @brief Clears current target.
    void clearTarget() noexcept { target = nullptr; }

    /// @brief Transfers and clears tower’s visual effects buffer.
    [[nodiscard]] std::vector<std::unique_ptr<VisualEffect>> getVisualEffects() noexcept;

protected:
    // --- Protected helpers ---
    /// @brief Selects the optimal target within range.
    [[nodiscard]] virtual Creature* selectTarget(const std::vector<std::unique_ptr<Creature>>& creatures);

    /// @brief Computes Euclidean distance between two points.
    [[nodiscard]] static float distance(const sf::Vector2f& a, const sf::Vector2f& b) noexcept;

    /// @brief Returns the texture name for the current frame.
    [[nodiscard]] virtual std::string getTextureName(int frame) const = 0;
};

#endif // TOWER_HPP
