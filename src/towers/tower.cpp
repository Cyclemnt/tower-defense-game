#include <cmath>
#include "../../include/towers/tower.hpp"
#include "../../include/creatures/creature.hpp"
#include "../../include/renderer/renderer.hpp"
#include "../../include/renderer/renderContext.hpp"
#include "../../include/visual-effects/tracerEffect.hpp"
#include "../../include/visual-effects/visualEffect.hpp"

Tower::Tower(int x_, int y_, int au, int ag, int cu, int dmg, float rng, float rate)
    : x(x_), y(y_), priceAu(au), priceAg(ag), priceCu(cu), damage(dmg), range(rng), fireRate(rate), level(1), cooldown(0.0f), target(nullptr) {}

int Tower::getX() const { return x; }

int Tower::getY() const { return y; }

int Tower::getLevel() const { return level; }

float Tower::getDamage() const { return damage; }

float Tower::getRange() const { return range; }

float Tower::getFireRate() const { return fireRate; }

std::array<int, 3> Tower::getPrice() const { return {priceAu, priceAg, priceCu}; }

const Creature* Tower::getTarget() const {return target; }

std::vector<std::unique_ptr<VisualEffect>> Tower::getVisualEffects() {
    // Moving visualEffects to temp
    std::vector<std::unique_ptr<VisualEffect>> temp = std::move(visualEffects);
    // Clearing visualEffects
    visualEffects.clear();
    return temp;
}

void Tower::update(float deltaTime, const std::vector<std::unique_ptr<Creature>>& creatures) {
    //std::cout << "twr cooldown: " << cooldown << std::endl;
    if (target || cooldown > 0.0f)
        cooldown -= deltaTime; // 1 tick = 1 time unit (1 frame)

    // Verify if actual target is still available
    if (target && (!target->isAlive() || std::sqrt(std::pow(target->getPosition()[0] - x, 2) + std::pow(target->getPosition()[1] - y, 2)) > range)) {
        target = nullptr; // Loosing lockdown
    }

    // Selecting new target if required
    if (!target) {
        if (cooldown < 0.0f)
            cooldown = 0.0f;  // Cooldown cannot be negative when target is lost
        target = selectTarget(creatures);
    }

    // Attack while cooldown let it
    while (target && cooldown <= 0.0f) {
        attack(target);
        cooldown += 1.0f / (fireRate); // seconds
        // Create tracer bullets
        std::array<float, 2> pos = {static_cast<float>(x), static_cast<float>(y)};
        visualEffects.push_back(std::make_unique<TracerEffect>(pos, target->getPosition()));
    }
}

void Tower::attack(Creature* target) {
    if (!target || !target->isAlive()) return;
    target->takeDamage(damage);
}

Creature* Tower::selectTarget(const std::vector<std::unique_ptr<Creature>>& creatures) {
    Creature* best = nullptr;
    float closest = std::numeric_limits<float>::max();

    for (auto& c : creatures) {
        if (!c->isAlive()) continue;

        float dx = c->getPosition()[0] - x;
        float dy = c->getPosition()[1] - y;
        float dist = std::sqrt(dx*dx + dy*dy);

        if (dist <= range) {
            if (!best || dist < closest) {
                best = c.get();
                closest = dist;
            }
        }
    }

    return best;
}

void Tower::upgrade() {
    level++;
    damage = static_cast<int>(damage * 1.5f);
    range += 1.0f;
    fireRate *= 1.2f;
}

void Tower::render(RenderContext& ctx) const {
    auto& window = ctx.window;
    auto& renderer = ctx.renderer;
    int frame = (ctx.tick / 8) % 4;

    std::string filename = getTextureName(frame);
    const sf::Texture& tex = renderer.getTexture(filename);

    sf::Sprite sprite(tex);
    const auto& sz = tex.getSize();

    sprite.setPosition({x * ctx.tileSize + ctx.offset.x, ctx.tileSize * (y + 0.8f - static_cast<float>(sz.y) / sz.x) + ctx.offset.y}); // y depends on image height

    sprite.setScale({ctx.tileSize / sz.x, ctx.tileSize / sz.x});
    window.draw(sprite);
}
