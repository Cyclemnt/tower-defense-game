#include "../../include/map/coreStorage.hpp"
#include "../../include/resources/cores.hpp"
#include "../../include/renderer.hpp"
#include "../../include/renderer/renderContext.hpp"

CoreStorage::CoreStorage(int x, int y, Cores* coresptr)
    : Tile(x, y), cores(coresptr) {}

bool CoreStorage::isWalkable() const { return true; }

bool CoreStorage::isBuildable() const { return false; }

std::string CoreStorage::getTextureName() const { return "tile_core.png"; }

int CoreStorage::getCoreCount() const { return cores->getSafe(); }

int CoreStorage::takeCores(int requested) { return cores->stealCore(requested); }

void CoreStorage::depositCores(int n) { cores->returnCore(n); }

void CoreStorage::render(const RenderContext& ctx) const {
    float ratio = 1.0f;
    int safe = cores->getSafe(), stolen = cores->getStolen(), lost = cores->getLost();
    int total = safe + stolen + lost;
    if (total > 0) ratio = static_cast<float>(safe) / total;

    std::string texName;
    if (ratio > 0.7f) texName = "tile_core_0.png";
    else if (ratio > 0.3f) texName = "tile_core_1.png";
    else texName = "tile_core_2.png";

    auto& renderer = ctx.renderer;
    const sf::Texture& tex = renderer.getTexture(texName);

    sf::Sprite sprite(tex);
    sprite.setPosition({getX() * ctx.tileSize, getY() * ctx.tileSize});
    sf::Vector2<unsigned int> sz = tex.getSize();
    sprite.setScale({ctx.tileSize / sz.x, ctx.tileSize / sz.y});
    ctx.window.draw(sprite);
}
