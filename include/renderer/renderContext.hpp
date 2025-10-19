#ifndef RENDER_CONTEXT_HPP
#define RENDER_CONTEXT_HPP

#include <SFML/Graphics.hpp>
#include <string>
class Renderer;

class RenderContext {
public:
    sf::RenderWindow& window;
    sf::Vector2u lastWinSize;  ///< Stores window size to detect changes
    Renderer& renderer;
    float tileSize;
    sf::Vector2f offset;
    int tick;

    RenderContext(sf::RenderWindow& w, Renderer& r, float ts = 64.0f, int t = 0);

    sf::Vector2i screenToTile(int mouseX, int mouseY) const;
};

#endif // RENDER_CONTEXT_HPP
