#ifndef RENDER_CONTEXT_HPP
#define RENDER_CONTEXT_HPP

#include <SFML/Graphics.hpp>
#include <string>
class Renderer;

class RenderContext {
public:
    sf::RenderWindow& window;
    const Renderer& renderer;
    float tileSize;
    int tick;

    RenderContext(sf::RenderWindow& w, const Renderer& r, float ts, int t)
        : window(w), renderer(r), tileSize(ts), tick(t) {}
};

#endif // RENDER_CONTEXT_HPP
