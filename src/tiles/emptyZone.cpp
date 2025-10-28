#include "../../include/tiles/emptyZone.hpp"
#include "../../include/renderer/renderContext.hpp"
#include "../../include/renderer/renderer.hpp"

EmptyZone::EmptyZone(sf::Vector2i position_) noexcept : Tile(position_) {}

std::string EmptyZone::getRandomTextureName() const noexcept {
    const uint32_t combined = static_cast<uint32_t>(
        (position.x * 73857093U) ^ (position.y * 19349663U) + kSeed);
    const uint32_t rnd = combined % 100U;

    if (rnd < 70U) return "tile_empty_1.png";
    if (rnd < 72U) return "tile_empty_2.png";
    if (rnd < 74U) return "tile_empty_4.png";
    if (rnd < 76U) return "tile_empty_5.png";
    if (rnd < 78U) return "tile_empty_6.png";
    if (rnd < 80U) return "tile_empty_7.png";
    if (rnd < 90U) return "tile_empty_3.png";
    if (rnd < 91U) return "tile_empty_8.png";
    return "tile_empty_0.png";
}

void EmptyZone::render(const RenderContext& ctx) const {
    if (!ctx.isOnScreen(static_cast<sf::Vector2f>(position))) return;

    const sf::Texture& tex = ctx.renderer.getTexture(getRandomTextureName());
    sf::Sprite sprite(tex);
    sprite.setPosition(static_cast<sf::Vector2f>(position) * ctx.tileSize + ctx.offset);

    const sf::Vector2u sz = tex.getSize();
    sprite.setScale({ctx.tileSize / sz.x, ctx.tileSize / sz.y});
    ctx.window.draw(sprite);
}
