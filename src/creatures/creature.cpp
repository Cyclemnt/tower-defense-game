#include <cmath>
#include <iostream>
#include "../../include/tiles/tile.hpp"
#include "../../include/creatures/creature.hpp"
#include "../../include/tiles/coreStorage.hpp"
#include "../../include/tiles/exitZone.hpp"
#include "../../include/renderer/renderer.hpp"
#include "../../include/renderer/renderContext.hpp"
#define PIf 3.141592f 

Creature::Creature(float health_, float shield_, float speed_, unsigned int coresCapacity_, Materials::Quantities loot_, bool boosted_)
    : health(health_), baseHealth(health_), shield(shield_), baseShield(shield_), speed(speed_), coresCapacity(coresCapacity_), loot(loot_), boosted(boosted_) {}

void Creature::update(float deltaTime) {
    if (!alive || path.empty() || pathIndex + 1 >= (int)path.size())
        return;

    float distanceToTravel = speed * deltaTime;

    while (distanceToTravel > 0.0f && pathIndex + 1 < path.size()) {
        const Tile* current = path[pathIndex];
        const Tile* next = path[pathIndex + 1];

        sf::Vector2i target = next->getPosition();

        sf::Vector2f d = sf::Vector2f(target) - position;
        float distanceToNextTile = d.length();

        if (distanceToTravel >= distanceToNextTile) {
            // Get to next Tile
            position = sf::Vector2f(target);
            pathIndex++;
            distanceToTravel -= distanceToNextTile;

            // Events depending on Tile
            if (const CoreStorage* c = dynamic_cast<const CoreStorage*>(next)) {
                if (coresCarried < coresCapacity) {
                    if (coresCapacity - coresCarried < 0) throw std::runtime_error("Creature carries more cores than its capacity");
                    stealCores(c->takeCores(coresCapacity - coresCarried)); // Taking as many cores as possible
                    distanceToTravel = 0.0f; // Path will change
                }
            }
            else if (const ExitZone* ex = dynamic_cast<const ExitZone*>(next)) {
                // Nothing to do, Game will do its job
            }
        } else {
            // Partially move thowards next Tile
            position += (d / distanceToNextTile) * distanceToTravel;
            distanceToTravel = 0.0f;
        }
    }
}

void Creature::takeDamage(float dmg) {
    if (!alive) return;

    float remaining = dmg;

    // Shield absorbs first
    if (shield > 0) {
        float absorbed = std::min(shield, remaining);
        shield -= absorbed;
        remaining -= absorbed;
        return; // Shield prevents taking damage to life once
    }

    // Then health
    if (remaining > 0) {
        health -= remaining;
        if (health <= 0) {
            alive = false;
        }
    }
}

unsigned int Creature::dropCores() noexcept {
    unsigned int dropped = coresCarried;
    coresCarried = 0;
    return dropped;
}

void Creature::leave() noexcept {
    loot = 0u;
    alive = false;
}

void Creature::render(const RenderContext& ctx) const {
    if (!ctx.isOnScreen(position)) return;

    Renderer& renderer = ctx.renderer;
    sf::RenderWindow& window = ctx.window;
    int frame = (ctx.tick / 8) % 4;

    std::string filename = getTextureName(frame);
    const sf::Texture& tex = renderer.getTexture(filename, true);

    sf::Sprite sprite(tex);
    sprite.setPosition({position.x * ctx.tileSize + ctx.offset.x, position.y * ctx.tileSize + ctx.offset.y});
    const auto& sz = tex.getSize();
    sprite.setScale({ctx.tileSize / sz.x, ctx.tileSize / sz.x});
    window.draw(sprite);

    drawCarriedCores(ctx);
    drawHealthBar(ctx);
}

void Creature::setPath(const std::vector<const Tile*>& p) {
    path = p;
    pathIndex = 0;
}

const Tile* Creature::getCurrentTile() const noexcept {
    if (path.empty() || pathIndex >= (int)path.size()) return nullptr;
    return path[pathIndex];
}

const Tile* Creature::getDestinationTile() const noexcept {
    if (path.empty()) return nullptr;
    return path.back();
}

const Tile* Creature::getNextTile() const noexcept {
    if (path.empty() || pathIndex + 1 >= (int)path.size()) return nullptr;
    return path[pathIndex + 1];
}

void Creature::stealCores(unsigned int amount) {
    coresCarried = std::min(coresCarried + amount, coresCapacity);
}

void Creature::drawHealthBar(const RenderContext& ctx) const {
    sf::RenderWindow& window = ctx.window;

    float hpRatio = health / baseHealth;
    float shieldRatio = baseShield > 0.0f ? shield / baseShield : 0.0f;

    const float barWidth = ctx.tileSize * 0.5f;
    const float barHeight = ctx.tileSize * 0.05f;
    const float x = position.x * ctx.tileSize + (ctx.tileSize - barWidth) * 0.5f + ctx.offset.x;
    const float baseY = position.y * ctx.tileSize - barHeight - 4.0f + ctx.offset.y;

    // Shield bar
    if (baseShield > 0.0f) {
        float y = baseY - (barHeight + 2.0f);
        sf::RectangleShape backBar({barWidth, barHeight});
        backBar.setFillColor(sf::Color(40, 40, 40));
        backBar.setPosition({x, y});
        window.draw(backBar);

        sf::RectangleShape shieldBar({barWidth * shieldRatio, barHeight});
        shieldBar.setFillColor(sf::Color(100, 150, 255, 200));
        shieldBar.setPosition({x, y});
        window.draw(shieldBar);
    }

    // Health bar
    {
        float y = baseY;
        sf::RectangleShape backBar({barWidth, barHeight});
        backBar.setFillColor(sf::Color(40, 40, 40));
        backBar.setPosition({x, y});
        window.draw(backBar);

        sf::Color lifeColor(255 * (1 - hpRatio), 255 * hpRatio, 0);
        sf::RectangleShape hpBar({barWidth * hpRatio, barHeight});
        hpBar.setFillColor(lifeColor);
        hpBar.setPosition({x, y});
        window.draw(hpBar);
    }
}

void Creature::drawCarriedCores(const RenderContext& ctx) const {
    if (coresCarried <= 0) return;
    
    float baseX = position.x * ctx.tileSize + ctx.offset.x + ctx.tileSize * 0.5f;
    float baseY = position.y * ctx.tileSize + ctx.offset.y + ctx.tileSize * 0.5f;

    float orbitRadius = ctx.tileSize * 0.15f;
    float angleStep = 2.0f * PIf / std::max(coresCarried, 1u);
    float time = ctx.tick * 0.03f; // Rotation speed
    float offset = static_cast<float>(reinterpret_cast<uintptr_t>(this) % 2048); // Some randomness (we should find something else)
    float coreRadius = ctx.tileSize * 0.03f;

    for (int i = 0; i < coresCarried; ++i) {
        float angle = time + i * angleStep + offset;
        float x = baseX + std::cos(angle) * orbitRadius;
        float y = baseY + std::sin(angle) * orbitRadius;

        sf::CircleShape core(coreRadius, 16);
        core.setOrigin(sf::Vector2f(coreRadius, coreRadius));
        core.setPosition(sf::Vector2f(x, y));

        sf::Color coreColor(100, 200, 255, 220);
        core.setFillColor(coreColor);

        core.setOutlineThickness(ctx.tileSize * 0.01f);
        core.setOutlineColor(sf::Color(150, 220, 255, 100));

        ctx.window.draw(core);
    }
}
