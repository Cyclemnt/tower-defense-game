#include "infrastructure/sfmlRenderer.hpp"
#include <SFML/Graphics.hpp>

namespace tdg::infra {

    SFMLRenderer::SFMLRenderer(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<SFMLResourceManager> ressources)
        : m_window(window), m_ressources(ressources) {}

    void SFMLRenderer::drawSprite(const std::string& spriteId, float x, float y) {
        if (!isInView(x, y)) return;
        const sf::Texture& texture = m_ressources->getTexture(spriteId);
        sf::Sprite sprite(texture);
        sprite.setPosition(sf::Vector2f(x, y));
        m_window->draw(sprite);
    }

    void SFMLRenderer::drawRectangle(float x, float y, float width, float height, int red, int green, int blue, int alpha) {
        if (!isInView(x, y)) return; // Considering the rectangle smaller than a tile
        sf::RectangleShape rectangle(sf::Vector2f(width, height));
        rectangle.setPosition(sf::Vector2f(x, y));
        rectangle.setFillColor(sf::Color(red, green, blue, alpha));
        m_window->draw(rectangle);
    }

    void SFMLRenderer::drawRectangle(float x1, float y1, float x2, float y2, float width, int red, int green, int blue, int alpha) {
        if (!isInView(x1, y1) && !isInView(x2, y2)) return;
        const sf::Vector2f startPoint = sf::Vector2f(x1, y1);
        const sf::Vector2f endPoint   = sf::Vector2f(x2, y2);
        const sf::Vector2f diff = endPoint - startPoint;
        const float length = diff.length();
        const sf::Angle angleDeg = diff.angle();

        sf::RectangleShape rectangle(sf::Vector2f(length, width));
        rectangle.setOrigin(sf::Vector2f(0.0f, width * 0.5f));
        rectangle.setPosition(startPoint);
        rectangle.setRotation(angleDeg);
        rectangle.setFillColor(sf::Color(red, green, blue, alpha));
        m_window->draw(rectangle);
    }

    void SFMLRenderer::drawCircle(float x, float y, float radius, int red, int green, int blue, int alpha) {
        if (!isInView(x, y)) return; // Considering the circle smaller than a tile
        sf::CircleShape circle(radius);
        circle.setPosition(sf::Vector2f(x - radius, y - radius));
        circle.setFillColor(sf::Color(red, green, blue, alpha));
        m_window->draw(circle);
    }

    bool SFMLRenderer::isInView(float x, float y) const {
        const sf::View& view = m_window->getView();
        sf::FloatRect viewBounds(
            view.getCenter() - view.getSize() * 0.5f,  // Top left corner
            view.getSize()                             // Size
        );
        sf::FloatRect objectBounds({x, y}, {*m_tileSize, *m_tileSize});
        return viewBounds.findIntersection(objectBounds).has_value();
    }

    
} // namespace tdg::infra
