#include "../../include/tiles/coreStorage.hpp"
#include "../../include/resources/cores.hpp"
#include "../../include/renderer/renderContext.hpp"
#include "../../include/renderer/renderer.hpp"

CoreStorage::CoreStorage(sf::Vector2i position_, Cores* coresPtr) noexcept
    : Tile(position_), cores(coresPtr) {}

unsigned int CoreStorage::takeCores(unsigned int requested) const noexcept {
    return cores ? cores->stealCore(requested) : 0u;
}

void CoreStorage::render(const RenderContext& ctx) const {
    if (!ctx.isOnScreen(static_cast<sf::Vector2f>(position))) return;

    const unsigned int safe = cores->getSafe();
    const unsigned int stolen = cores->getStolen();
    const unsigned int lost = cores->getLost();
    const unsigned int total = safe + stolen + lost;

    float ratio = total > 0 ? static_cast<float>(safe) / static_cast<float>(total) : 1.0f;

    std::string textureName =
        (ratio == 1.0f) ? "tile_core_0.png" :
        (ratio > 0.5f) ? "tile_core_1.png" :
        (ratio > 0.0f) ? "tile_core_2.png" :
                         "tile_core_3.png";

    const sf::Texture& tex = ctx.renderer.getTexture(textureName);
    sf::Sprite sprite(tex);
    sprite.setPosition(static_cast<sf::Vector2f>(position) * ctx.tileSize + ctx.offset);

    const sf::Vector2u sz = tex.getSize();
    sprite.setScale({ctx.tileSize / sz.x, ctx.tileSize / sz.y});
    ctx.window.draw(sprite);
}
