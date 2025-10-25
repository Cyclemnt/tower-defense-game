#include <cmath>
#include <iostream>
#include "../../include/tiles/tile.hpp"
#include "../../include/creatures/creature.hpp"
#include "../../include/tiles/coreStorage.hpp"
#include "../../include/tiles/exitZone.hpp"
#include "../../include/renderer/renderer.hpp"
#include "../../include/renderer/renderContext.hpp"

Creature::Creature(float hp, float sh, float spd, int coresCapacity_, int au_, int ag_, int cu_)
    : health(hp), baseHealth(hp), shield(sh), baseShield(sh), speed(spd), coresCapacity(coresCapacity_), au(au_), ag(ag_), cu(cu_), coresCarried(0),
    pathIndex(0), alive(true) {}

bool Creature::isAlive() const { return alive; }

float Creature::getHealth() const { return health; }

float Creature::getBaseHealth() const { return baseHealth; }

float Creature::getShield() const { return shield; }

float Creature::getBaseShield() const { return baseShield; }

float Creature::getSpeed() const { return speed; }

int Creature::getCoresCarried() const { return coresCarried; }

std::array<int, 3> Creature::getLoot() const { return {au, ag, cu}; }

void Creature::setPath(const std::vector<Tile*>& p) {
    path = p;
    pathIndex = 0;
}

void Creature::setPosition(std::array<int, 2> pos) {
    posX = pos[0];
    posY = pos[1];
}

std::array<float, 2> Creature::getPosition() const {
    return {posX, posY};
}

Tile* Creature::getCurrentTile() const {
    if (path.empty() || pathIndex >= (int)path.size()) return nullptr;
    return path[pathIndex];
}

Tile* Creature::getNextTile() const {
    if (path.empty() || pathIndex + 1 >= (int)path.size()) return nullptr;
    return path[pathIndex + 1];
}

Tile* Creature::getDestinationTile() const {
    if (path.empty()) return nullptr;
    return path.back();
}

void Creature::update(float deltaTime) {
    if (!alive || path.empty() || pathIndex + 1 >= (int)path.size())
        return;

    float distanceToTravel = speed * deltaTime;

    while (distanceToTravel > 0.0f && pathIndex + 1 < (int)path.size()) {
        Tile* current = path[pathIndex];
        Tile* next = path[pathIndex + 1];

        float targetX = next->getX();
        float targetY = next->getY();

        float dx = targetX - posX;
        float dy = targetY - posY;
        float distToNext = std::sqrt(dx * dx + dy * dy);

        if (distanceToTravel >= distToNext) {
            // Get to next Tile
            posX = targetX;
            posY = targetY;
            pathIndex++;
            distanceToTravel -= distToNext;

            // Events depending on Tile
            if (CoreStorage* c = dynamic_cast<CoreStorage*>(next)) {
                if (coresCarried < coresCapacity) {
                    stealCores(c->takeCores(coresCapacity - coresCarried)); // Taking as many cores as possible
                    distanceToTravel = 0.0f; // Path will change
                }
            }
            else if (ExitZone* ex = dynamic_cast<ExitZone*>(next)) {
                // if (coresCarried > 0) {
                //     coresCarried = 0;
                // }
            }
        } else {
            // Partially move thowards next Tile
            posX += (dx / distToNext) * distanceToTravel;
            posY += (dy / distToNext) * distanceToTravel;
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
        return;
    }

    // Then health
    if (remaining > 0) {
        health -= remaining;
        if (health <= 0) {
            alive = false;
        }
    }
}

void Creature::stealCores(int amount) {
    coresCarried += amount;
}

int Creature::dropCores() {
    int dropped = coresCarried;
    coresCarried = 0;
    return dropped;
}

void Creature::leave() {
    au = 0;
    ag = 0;
    cu = 0;
    alive = false;
}

void Creature::render(RenderContext& ctx) const {
    auto& renderer = ctx.renderer;
    auto& window = ctx.window;
    int frame = (ctx.tick / 8) % 4;

    std::string filename = getTextureName(frame);
    const sf::Texture& tex = renderer.getTexture(filename, true);

    sf::Sprite sprite(tex);
    sprite.setPosition({posX * ctx.tileSize + ctx.offset.x, posY * ctx.tileSize + ctx.offset.y});
    const auto& sz = tex.getSize();
    sprite.setScale({ctx.tileSize / sz.x, ctx.tileSize / sz.x});
    window.draw(sprite);

    drawFloatingCores(ctx);

    drawHealthBar(ctx);
}

void Creature::drawFloatingCores(RenderContext& ctx) const {
    if (coresCarried <= 0) return;
    
    float baseX = posX * ctx.tileSize + ctx.offset.x + ctx.tileSize * 0.5f;
    float baseY = posY * ctx.tileSize + ctx.offset.y + ctx.tileSize * 0.5f;

    float orbitRadius = ctx.tileSize * 0.15f;
    float angleStep = 2.0f * M_PIf / std::max(coresCarried, 1);
    float time = ctx.tick * 0.03f; // Rotation speed
    float offset = static_cast<float>(reinterpret_cast<uintptr_t>(this) % 2048); // Some randomness
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

void Creature::drawHealthBar(RenderContext& ctx) const {
    auto& window = ctx.window;

    float hpRatio = health / baseHealth;
    float shieldRatio = baseShield > 0.0f ? shield / baseShield : 0.0f;

    const float barWidth = ctx.tileSize * 0.5f;
    const float barHeight = ctx.tileSize * 0.05f;
    const float x = posX * ctx.tileSize + (ctx.tileSize - barWidth) * 0.5f + ctx.offset.x;
    const float baseY = posY * ctx.tileSize - barHeight - 4.0f + ctx.offset.y;

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
