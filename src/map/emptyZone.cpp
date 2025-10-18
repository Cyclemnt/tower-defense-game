#include "../../include/map/emptyZone.hpp"
#include "../../include/renderer/renderer.hpp"
#include "../../include/renderer/renderContext.hpp"

EmptyZone::EmptyZone(int x, int y)
    : Tile(x, y) {}

EmptyZone::~EmptyZone() {}

bool EmptyZone::isWalkable() const { return false; }

bool EmptyZone::isBuildable() const { return false; }

std::string EmptyZone::getTextureName() const { return "tile_empty.png"; }

const std::string EmptyZone::getRandomTextureName(int x, int y) const {
    // Combine data with multiplication and bit shift
    uint32_t combined = (x * 73856093U) ^ (y * 19349663U);
    combined += emptyTileSeed & 0xFFFFFFFF; // Add seed
    uint32_t rnd = combined % 100;

    // Probability distribution:
    if (rnd < 70u) return "tile_empty_1.png";
    else if (rnd < 72u) return "tile_empty_2.png";
    else if (rnd < 74u) return "tile_empty_4.png";
    else if (rnd < 76u) return "tile_empty_5.png";
    else if (rnd < 78u) return "tile_empty_6.png";
    else if (rnd < 80u) return "tile_empty_7.png";
    else if (rnd < 90u) return "tile_empty_3.png";
    else return "tile_empty_0.png";
}

void EmptyZone::render(const RenderContext& ctx) const {
    auto& renderer = ctx.renderer;
    const sf::Texture& tex = renderer.getTexture(getRandomTextureName(getX(), getY()));

    sf::Sprite sprite(tex);
    sprite.setPosition({getX() * ctx.tileSize + ctx.offset.x, getY() * ctx.tileSize + ctx.offset.y});
    auto sz = tex.getSize();
    sprite.setScale({ctx.tileSize / sz.x, ctx.tileSize / sz.y});
    ctx.window.draw(sprite);
}
