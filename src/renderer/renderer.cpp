#include <iostream>
#include "../../include/renderer/renderer.hpp"
#include "../../include/visual-effects/visualEffect.hpp"
#include "../../include/game.hpp"
#include "../../include/towers/tower.hpp"
#include "../../include/map/openZone.hpp"

Renderer::Renderer(sf::RenderWindow& win, Game& game)
    : game(game), ctx(win, *this)
{
    // Set icon
    sf::Texture iconSprite(getTexture("icon.png"));
    sf::Image iconImage = iconSprite.copyToImage(); 
    ctx.window.setIcon({iconImage.getSize().x, iconImage.getSize().y}, iconImage.getPixelsPtr());

    computeScaling();
}

const sf::Texture& Renderer::getTexture(const std::string& filename) {
    auto it = textures.find(filename);
    if (it != textures.end())
        return it->second;

    sf::Texture tex;
    if (!tex.loadFromFile("../assets/textures/" + filename)) {
        std::cerr << "[Renderer] Missing texture: " << filename << std::endl;
        if (!tex.loadFromFile("../assets/textures/missing_texture.png"))
            std::cerr << "Failed to load fallback texture.\n";
    }

    // TODO: if creature, setSmooth true, else :
    tex.setSmooth(false);
    textures[filename] = std::move(tex);
    return textures.at(filename);
}

void Renderer::computeScaling() {
    const Map& map = game.getMap();
    const int mapWidth = map.getWidth();
    const int mapHeight = map.getHeight();

    sf::Vector2u winSize = ctx.window.getSize();

    float scaleX = static_cast<float>(winSize.x) / (mapWidth * ctx.tileSize);
    float scaleY = static_cast<float>(winSize.y) / (mapHeight * ctx.tileSize);

    float scaleFactor = std::min(scaleX, scaleY);
    ctx.tileSize *= scaleFactor;

    // Center the map inside the window
    float mapWidthPx  = mapWidth  * ctx.tileSize;
    float mapHeightPx = mapHeight * ctx.tileSize;
    ctx.offset.x = (winSize.x - mapWidthPx) * 0.5f;
    ctx.offset.y = (winSize.y - mapHeightPx) * 0.5f;

    // Adjust SFML view (maintains correct aspect ratio)
    sf::View view(sf::FloatRect({0, 0}, {static_cast<float>(winSize.x), static_cast<float>(winSize.y)}));
    ctx.window.setView(view);
}

void Renderer::render() {
    ctx.tick = game.getTick();

    // Recalculate scaling if window size changed
    sf::Vector2u winSize = ctx.window.getSize();
    if (winSize != ctx.lastWinSize) {
        computeScaling();
        ctx.lastWinSize = winSize;
    }

    // --- Draw map ---
    game.getMap().render(ctx);

    // --- Highlight tile under mouse ---
    highlightTile();

    // --- Draw creatures ---
    for (const auto& creature : game.getCreatures())
        creature->render(ctx);

    // --- Draw towers ---
    for (const auto& tower : game.getTowers())
        tower->render(ctx);

    // --- Draw visual effects ---
    for (const auto& effect : game.getVisualEffects())
        effect->render(ctx);
}

void Renderer::highlightTile() {
    const Map& map = game.getMap();
    sf::Vector2i mouse = sf::Mouse::getPosition(ctx.window);
    sf::Vector2i tilePos = ctx.screenToTile(mouse.x, mouse.y);

    if (tilePos.x < 0 || tilePos.x >= map.getWidth() ||
        tilePos.y < 0 || tilePos.y >= map.getHeight())
        return;

    Tile* tile = map.getTile(tilePos.x, tilePos.y);
    if (!tile->isBuildable())
        return;

    OpenZone* openZoneTile = dynamic_cast<OpenZone*>(tile);
    sf::RectangleShape highlight({ctx.tileSize, ctx.tileSize});
    highlight.setPosition({
        tilePos.x * ctx.tileSize + ctx.offset.x,
        tilePos.y * ctx.tileSize + ctx.offset.y
    });
    if (openZoneTile->isOccupied()) highlight.setFillColor(sf::Color(255, 50, 50, 80)); // Red
    else highlight.setFillColor(sf::Color(50, 200, 50, 80)); // Green

    ctx.window.draw(highlight);
}
