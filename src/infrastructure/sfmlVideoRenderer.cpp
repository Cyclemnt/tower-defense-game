#include <SFML/Graphics.hpp>
#include <iostream>
#include "infrastructure/sfmlVideoRenderer.hpp"

namespace tdg::infra {

    SFMLVideoRenderer::SFMLVideoRenderer(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<SFMLResourceManager> ressources, std::shared_ptr<float> tileSize)
        : m_window(window), m_ressources(ressources), m_tileSize(tileSize)
    {
        if (!m_font.openFromFile("../assets/fonts/lexend-black.ttf")) {
            std::cerr << "Failed to load font ../assets/lexend-black.ttf\n";
        }
    }

    void SFMLVideoRenderer::drawSprite(const std::string& spriteId, float x, float y, float size, bool worldCoordinates) {
        try {
            if (worldCoordinates) { x *= *m_tileSize; y *= *m_tileSize; size *= *m_tileSize; }
            if (!isInView(x, y)) return;
            const sf::Texture& texture = m_ressources->getTexture(spriteId);
            sf::Sprite sprite(texture);
            sprite.setPosition(sf::Vector2f(x, y));
            sf::Vector2u texSize = texture.getSize();

            float scale = size / static_cast<float>(texSize.x);
            // if (worldCoordinates) { scale *= *m_tileSize; }

            sprite.setScale(sf::Vector2f(scale, scale));
            m_window->draw(sprite);
        }
        catch (...) {}
    }

    void SFMLVideoRenderer::drawRectangle(float x, float y, float width, float height, utils::Color fill, float thickness, utils::Color outline, bool worldCoordinates) {
        if (worldCoordinates) { x *= *m_tileSize; y *= *m_tileSize; width *= *m_tileSize; height *= *m_tileSize; thickness *= *m_tileSize; }
        if (!isInView(x, y)) return; // Considering the rectangle smaller than a tile
        sf::RectangleShape rectangle(sf::Vector2f(width, height));
        rectangle.setPosition(sf::Vector2f(x, y));
        rectangle.setFillColor(sf::Color(fill.r, fill.g, fill.b, fill.a));
        if (thickness > 0.0f) rectangle.setOutlineThickness(thickness);
        rectangle.setOutlineColor(sf::Color(outline.r, outline.g, outline.b, outline.a));
        m_window->draw(rectangle);
    }

    void SFMLVideoRenderer::drawLine(float x1, float y1, float x2, float y2, float width, utils::Color fill, float thickness, utils::Color outline, bool worldCoordinates) {
        if (worldCoordinates) { x1 *= *m_tileSize; y1 *= *m_tileSize; x2 *= *m_tileSize; y2 *= *m_tileSize; width *= *m_tileSize; thickness *= *m_tileSize; }
        if (!isInView(x1, y1) && !isInView(x2, y2)) return;
        const sf::Vector2f startPoint = sf::Vector2f(x1, y1);
        const sf::Vector2f endPoint   = sf::Vector2f(x2, y2);
        const sf::Vector2f diff = endPoint - startPoint;
        const float length = diff.length();
        const sf::Angle angle = diff.angle();

        sf::RectangleShape rectangle(sf::Vector2f(length, width));
        rectangle.setOrigin(sf::Vector2f(0.0f, width * 0.5f));
        rectangle.setPosition(startPoint);
        rectangle.setRotation(angle);
        rectangle.setFillColor(sf::Color(fill.r, fill.g, fill.b, fill.a));
        rectangle.setOutlineThickness(thickness);
        rectangle.setOutlineColor(sf::Color(outline.r, outline.g, outline.b, outline.a));
        m_window->draw(rectangle);
    }

    void SFMLVideoRenderer::drawCircle(float x, float y, float radius, utils::Color fill, float thickness, utils::Color outline, bool worldCoordinates) {
        if (worldCoordinates) { x *= *m_tileSize; y *= *m_tileSize; radius *= *m_tileSize; thickness *= *m_tileSize; }
        if (!isInView(x, y)) return; // Considering the circle smaller than a tile
        sf::CircleShape circle(radius);
        circle.setPosition(sf::Vector2f(x - radius, y - radius));
        circle.setFillColor(sf::Color(fill.r, fill.g, fill.b, fill.a));
        circle.setOutlineThickness(thickness);
        circle.setOutlineColor(sf::Color(outline.r, outline.g, outline.b, outline.a));
        m_window->draw(circle);
    }

    void SFMLVideoRenderer::drawText(const std::string& text, float size, float x, float y, utils::Color color, bool worldCoordinates) {
        if (worldCoordinates) { x *= *m_tileSize; y *= *m_tileSize; }
        sf::Text txt(m_font, text, size);
        txt.setPosition(sf::Vector2f(x, y));
        txt.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
        m_window->draw(txt);
    }

    bool SFMLVideoRenderer::isInView(float x, float y) const {
        const sf::View& view = m_window->getView();
        sf::FloatRect viewBounds(
            view.getCenter() - view.getSize() * 0.5f,  // Top left corner
            view.getSize()                             // Size
        );
        sf::FloatRect objectBounds({x, y}, {*m_tileSize, *m_tileSize});
        return viewBounds.findIntersection(objectBounds).has_value();
    }

} // namespace tdg::infra
