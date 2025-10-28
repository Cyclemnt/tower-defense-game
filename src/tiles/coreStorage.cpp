#include "../../include/tiles/coreStorage.hpp"
#include "../../include/resources/cores.hpp"
#include "../../include/renderer/renderer.hpp"
#include "../../include/renderer/renderContext.hpp"

CoreStorage::CoreStorage(sf::Vector2i position_, Cores* coresptr)
    : Tile(position_), cores(coresptr) {}

bool CoreStorage::isWalkable() const { return true; }

bool CoreStorage::isBuildable() const { return false; }

std::string CoreStorage::getTextureName() const { return "tile_core.png"; }

int CoreStorage::getCoreCount() const { return cores->getSafe(); }

int CoreStorage::takeCores(int requested) const { return cores->stealCore(requested); }

void CoreStorage::depositCores(int n) { cores->returnCore(n); }

void CoreStorage::render(const RenderContext& ctx) const {
    if (!ctx.isOnScreen(static_cast<sf::Vector2f>(position))) return;
    
    float ratio = 1.0f;
    int safe = cores->getSafe(), stolen = cores->getStolen(), lost = cores->getLost();
    int total = safe + stolen + lost;
    if (total > 0) ratio = static_cast<float>(safe) / total;

    std::string texName;
    if (ratio == 1.0f) texName = "tile_core_0.png";
    else if (ratio > 0.5f) texName = "tile_core_1.png";
    else if (ratio > 0.0f) texName = "tile_core_2.png";
    else texName = "tile_core_3.png";

    auto& renderer = ctx.renderer;
    const sf::Texture& tex = renderer.getTexture(texName);

    sf::Sprite sprite(tex);
    sprite.setPosition(sf::Vector2f(position) * ctx.tileSize + ctx.offset);
    sf::Vector2<unsigned int> sz = tex.getSize();
    sprite.setScale({ctx.tileSize / sz.x, ctx.tileSize / sz.y});
    ctx.window.draw(sprite);
}
