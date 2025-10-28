#include "../../include/renderer/renderContext.hpp"

RenderContext::RenderContext(sf::RenderWindow& w, Renderer& r, float ts, int t)
        : window(w), renderer(r), tileSize(ts), tick(t), lastWinSize(window.getSize()) {}

sf::Vector2i RenderContext::screenToTile(int mouseX, int mouseY) const {
    float localX = (mouseX - offset.x) / tileSize;
    float localY = (mouseY - offset.y) / tileSize;
    return { static_cast<int>(localX), static_cast<int>(localY) };
}

bool RenderContext::isOnScreen(const sf::Vector2f& position) const {
    sf::Vector2f pixelsFromWindowOrigin = position * tileSize + offset;

    if (pixelsFromWindowOrigin.x > window.getSize().x || pixelsFromWindowOrigin.y > window.getSize().y ||
        pixelsFromWindowOrigin.x < -tileSize || pixelsFromWindowOrigin.y < -tileSize)
        return false;
    else return true;
}