#include "../../include/renderer/renderContext.hpp"

RenderContext::RenderContext(sf::RenderWindow& w, Renderer& r, float ts, int t)
        : window(w), renderer(r), tileSize(ts), tick(t), lastWinSize(window.getSize()) {}

sf::Vector2i RenderContext::screenToTile(int mouseX, int mouseY) const {
    float localX = (mouseX - offset.x) / tileSize;
    float localY = (mouseY - offset.y) / tileSize;
    return { static_cast<int>(localX), static_cast<int>(localY) };
}
