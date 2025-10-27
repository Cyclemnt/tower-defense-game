#include "../../include/tiles/tile.hpp"
#include "../../include/renderer/renderer.hpp"
#include "../../include/renderer/renderContext.hpp"

Tile::Tile(sf::Vector2i position_)
    : position(position_) {}

void Tile::render(const RenderContext& ctx) const {
    auto& renderer = ctx.renderer;
    const sf::Texture& tex = renderer.getTexture(getTextureName());

    sf::Sprite sprite(tex);
    sprite.setPosition(sf::Vector2f(position) * ctx.tileSize + ctx.offset);
    auto sz = tex.getSize();
    sprite.setScale({ctx.tileSize / sz.x, ctx.tileSize / sz.y});
    ctx.window.draw(sprite);
}

void Tile::setCoords(sf::Vector2i position_) {
    position = position_;
}
