#include <iostream>
#include "../../include/renderer/renderer.hpp"
#include "../../include/visual-effects/visualEffect.hpp"
#include "../../include/game.hpp"
#include "../../include/towers/tower.hpp"
#include "../../include/tiles/openZone.hpp"
#include "../../include/map/map.hpp"

Renderer::Renderer(sf::RenderWindow& win, Game& game_)
    : game(game_), ctx(win, *this)
{
    // Load and set window icon
    const sf::Texture& iconTex = getTexture("icon.png");
    const sf::Image icon = iconTex.copyToImage();
    ctx.window.setIcon(icon.getSize(), icon.getPixelsPtr());

    computeScaling();
}

const sf::Texture& Renderer::getTexture(const std::string& filename, bool smooth) {
    if (auto it = textures.find(filename); it != textures.end())
        return it->second;

    sf::Texture tex;
    if (!tex.loadFromFile("../assets/textures/" + filename)) {
        std::cerr << "[Renderer] Missing texture: " << filename << std::endl;
        if (!tex.loadFromFile("../assets/textures/missing_texture.png"))
            std::cerr << "Failed to load fallback texture.\n";
    }

    tex.setSmooth(smooth);
    auto [insertedIt, _] = textures.emplace(filename, std::move(tex));
    return insertedIt->second;
}

void Renderer::computeScaling() {
    const Map& map = game.getMap();
    const sf::Vector2u mapSize = map.getSize();
    sf::Vector2f winSize = static_cast<sf::Vector2f>(ctx.window.getSize());

    float scaleX = winSize.x / (mapSize.x * ctx.tileSize);
    float scaleY = winSize.y / (mapSize.y * ctx.tileSize);
    float scaleFactor = std::min(scaleX, scaleY);
    
    ctx.tileSize *= scaleFactor;

    // Center the map inside the window
    sf::Vector2f mapSizePx = static_cast<sf::Vector2f>(mapSize) * ctx.tileSize;
    ctx.offset = (static_cast<sf::Vector2f>(winSize) - mapSizePx) * 0.5f;

    // Adjust SFML view (maintains correct aspect ratio)
    sf::View view(sf::FloatRect({0, 0}, winSize));
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
    if (game.isOver()) return;
    
    const Map& map = game.getMap();
    sf::Vector2i mousePos = sf::Mouse::getPosition(ctx.window);
    sf::Vector2i tilePos = ctx.screenToTile(mousePos);

    Tile* tile = map.getTile(tilePos);
    if (!tile) return;
    if (!tile->isBuildable()) return;

    OpenZone* openZoneTile = dynamic_cast<OpenZone*>(tile);
    sf::RectangleShape highlight({ctx.tileSize, ctx.tileSize});
    highlight.setPosition(static_cast<sf::Vector2f>(tilePos) * ctx.tileSize + ctx.offset);

    sf::Color color;
    bool isOccupied = openZoneTile->isOccupied();
    switch (game.playerState) {
        case Player::State::Building:
            if (isOccupied) color = sf::Color(50, 50, 50, 80); // Gray
            else color = sf::Color(50, 200, 50, 80); // Green
            break;
        case Player::State::Selling:
            if (isOccupied) color = sf::Color(255, 50, 50, 80); // Red
            else color = sf::Color(50, 50, 50, 80); // Gray
            break;
        case Player::State::None: [[fallthrough]];
        default: color = sf::Color(50, 50, 50, 80); break;
    }
    
    highlight.setFillColor(color);
    ctx.window.draw(highlight);
}
