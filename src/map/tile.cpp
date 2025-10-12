#include "../../include/map/tile.hpp"
#include "../../include/renderer.hpp"
#include "../../include/renderer/renderContext.hpp"

Tile::Tile(int x_, int y_)
    : x(x_), y(y_) {}

int Tile::getX() const { return x; }

int Tile::getY() const { return y; }

void Tile::render(const RenderContext& ctx) const {
    const sf::Texture& tex = Renderer::getTextureStatic(getTextureName());

    sf::Sprite sprite(tex);
    sprite.setPosition({x * ctx.tileSize, y * ctx.tileSize});
    auto sz = tex.getSize();
    sprite.setScale({ctx.tileSize / sz.x, ctx.tileSize / sz.y});
    ctx.window.draw(sprite);
}