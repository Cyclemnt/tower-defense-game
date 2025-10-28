#include "../../include/tiles/tile.hpp"
#include "../../include/renderer/renderer.hpp"
#include "../../include/renderer/renderContext.hpp"

Tile::Tile(sf::Vector2i position_) noexcept : position(position_) {}

void Tile::render(const RenderContext& ctx) const {
    if (!ctx.isOnScreen(static_cast<sf::Vector2f>(position))) return;

    const sf::Texture& tex = ctx.renderer.getTexture(getTextureName());
    sf::Sprite sprite(tex);
    sprite.setPosition(static_cast<sf::Vector2f>(position) * ctx.tileSize + ctx.offset);

    const sf::Vector2u sz = tex.getSize();
    sprite.setScale({ctx.tileSize / sz.x, ctx.tileSize / sz.y});
    ctx.window.draw(sprite);
}
