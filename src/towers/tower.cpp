#include <cmath>
#include "../../include/towers/tower.hpp"
#include "../../include/creatures/creature.hpp"
#include "../../include/renderer/renderer.hpp"
#include "../../include/renderer/renderContext.hpp"
#include "../../include/visual-effects/tracerEffect.hpp"

Tower::Tower(sf::Vector2i position_, std::array<unsigned int, 3> cost_, float damage_, float range_, float fireRate_) noexcept
    : position(position_), cost(cost_), damage(damage_), range(range_), fireRate(fireRate_) {}

void Tower::update(float deltaTime, const std::vector<std::unique_ptr<Creature>>& creatures) {
    if (target || cooldown > 0.0f)
        cooldown -= deltaTime;

    // Validate target
    if (target && (!target->isAlive() || distance(static_cast<sf::Vector2f>(position), target->getPosition()) > range))
        clearTarget();

    // Acquire new target if needed
    if (!target) {
        cooldown = std::max(cooldown, 0.0f);
        target = selectTarget(creatures);
    }

    // Attack while cooldown allows
    while (target && cooldown <= 0.0f) {
        attack(target);
        cooldown += 1.0f / fireRate;
        visualEffects.push_back(std::make_unique<TracerEffect>(static_cast<sf::Vector2f>(position), target->getPosition()));
    }
}

void Tower::attack(Creature* target_) {
    if (!target_ || !target_->isAlive()) return;
    target_->takeDamage(damage);
}

void Tower::upgrade() {
    // Basic upgrade rule, subclasses may override
    level++;
    damage *= 1.2f;
    range *= 1.05f;
    fireRate *= 1.1f;
}

void Tower::render(const RenderContext& ctx) const {
    auto& renderer = ctx.renderer;
    auto& window = ctx.window;

    const int frame = (ctx.tick / 8) % 4;
    const std::string filename = getTextureName(frame);
    const sf::Texture& tex = renderer.getTexture(filename);

    sf::Sprite sprite(tex);
    const auto& sz = tex.getSize();

    sprite.setPosition({
        position.x * ctx.tileSize + ctx.offset.x,
        ctx.tileSize * (position.y + 0.8f - static_cast<float>(sz.y) / sz.x) + ctx.offset.y
    });

    sprite.setScale({ctx.tileSize / sz.x, ctx.tileSize / sz.x});
    window.draw(sprite);
}

std::vector<std::unique_ptr<VisualEffect>> Tower::getVisualEffects() noexcept {
    auto temp = std::move(visualEffects);
    visualEffects.clear();
    return temp;
}

Creature* Tower::selectTarget(const std::vector<std::unique_ptr<Creature>>& creatures) {
    Creature* best = nullptr;
    float closest = std::numeric_limits<float>::max();

    for (auto& c : creatures) {
        if (!c->isAlive()) continue;
        const float dist = distance(static_cast<sf::Vector2f>(position), c->getPosition());
        if (dist <= range && dist < closest) {
            closest = dist;
            best = c.get();
        }
    }

    return best;
}

float Tower::distance(const sf::Vector2f& a, const sf::Vector2f& b) noexcept {
    const sf::Vector2f d = b - a;
    return std::sqrt(d.x * d.x + d.y * d.y);
}
