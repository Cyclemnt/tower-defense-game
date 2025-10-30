#include "../../include/renderer/renderContext.hpp"
#include "../../include/renderer/renderer.hpp"

RenderContext::RenderContext(sf::RenderWindow& w, Renderer& r) noexcept
    : window(w), renderer(r), lastWinSize(window.getSize()) {}

sf::Vector2i RenderContext::screenToTile(const sf::Vector2i& mousePos) const noexcept {
    const sf::Vector2i tilePos = static_cast<sf::Vector2i>((static_cast<sf::Vector2f>(mousePos) - offset) / tileSize);
    return tilePos;
}

bool RenderContext::isOnScreen(const sf::Vector2f& position) const noexcept {
    const sf::Vector2f pixels = position * tileSize + offset;
    const sf::Vector2u win = window.getSize();

    return !(pixels.x > win.x || pixels.y > win.y || pixels.x < -tileSize || pixels.y < -tileSize);
}
