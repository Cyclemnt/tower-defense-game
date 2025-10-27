#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <string>
#include <array>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "../resources/materials.hpp"

class Tile;
class RenderContext;

/**
 * @class Creature
 * @brief Abstract base class for all enemy units.
 *
 * A Creature represents an enemy entity moving along a predefined path toward
 * the CoreStorage. It possesses health, shields, speed, and may carry cores.
 * When defeated, it drops its loot and any carried cores.
 */
class Creature {
public:
    /// @brief Lists all enemy creature archetypes.
    enum class Type {
        Minion, MinionB,
        Drone, DroneB,
        Tank, TankB
    };

private:
    // --- Spatial data ---
    sf::Vector2f position; ///< World-space coordinates (in tile units).

    // --- Stats ---
    const float baseHealth; ///< Initial health (for UI reference).
    const float baseShield; ///< Initial shield (for UI reference).
    float health;           ///< Current health.
    float shield;           ///< Current shield.
    float speed;            ///< Movement speed (tiles per second).

    // --- Loot and cores ---
    Materials::Quantities loot;       ///< Loot granted on death.
    unsigned int coresCarried = 0;    ///< Number of cores currently carried.
    const unsigned int coresCapacity; ///< Maximum number of cores that can be carried.

    // --- Path following ---
    std::vector<const Tile*> path; ///< Ordered list of tiles composing the route.
    size_t pathIndex = 0;          ///< Current index in the path.

    bool alive = true; ///< Whether the creature is alive.

protected:
    bool boosted = false; ///< Whether this creature is a boosted variant.

public:
    /// @brief Constructs a new creature with specified attributes.
    /// @param health_ Initial health value.
    /// @param shield_ Initial shield value.
    /// @param speed_ Movement speed in tiles per second.
    /// @param coresCapacity_ Maximum number of cores the creature can carry.
    /// @param loot_ Loot granted to the player upon death.
    /// @param boosted_ Whether this creature is a boosted variant.
    Creature(float health_, float shield_, float speed_, unsigned int coresCapacity_, Materials::Quantities loot_, bool boosted_);

    /// @brief Virtual destructor.
    virtual ~Creature() = default;

    /// @brief Updates movement and interactions with the map.
    /// @param deltaTime Elapsed time since last update (in seconds).
    virtual void update(float deltaTime);

    /// @brief Applies damage to the creature, consuming shields first.
    /// @param dmg Amount of damage dealt.
    virtual void takeDamage(float dmg);

    /// @brief Drops all carried cores (called on death).
    /// @return Number of cores dropped.
    virtual unsigned int dropCores() noexcept;

    /// @brief Removes the creature from play (e.g., upon exit).
    virtual void leave() noexcept;

    /// @brief Renders the creature to the screen.
    virtual void render(const RenderContext& ctx) const;

    // --- Basic getters ---
    [[nodiscard]] sf::Vector2f getPosition() const noexcept { return position; }
    [[nodiscard]] Materials::Quantities getLoot() const noexcept { return loot; }
    [[nodiscard]] bool isAlive() const noexcept { return alive; }

    // --- Path handling ---
    void setPath(const std::vector<const Tile*>& newPath);
    void setPosition(const sf::Vector2i tileCoords) { position = sf::Vector2f(tileCoords); }
    [[nodiscard]] const Tile* getCurrentTile() const noexcept;
    [[nodiscard]] const Tile* getDestinationTile() const noexcept;

private:
    // --- Private helpers ---
    [[nodiscard]] virtual std::string getTextureName(int frame) const = 0;
    
    [[nodiscard]] const Tile* getNextTile() const noexcept;
    void stealCores(unsigned int amount);
    void drawHealthBar(const RenderContext& ctx) const;
    void drawCarriedCores(const RenderContext& ctx) const;
};

#endif // CREATURE_HPP
