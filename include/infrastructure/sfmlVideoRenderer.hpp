#ifndef SFML_VIDEO_RENDERER_HPP
#define SFML_VIDEO_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "core/interfaces/iVideoRenderer.hpp"
#include "infrastructure/sfmlResourceManager.hpp"

namespace tdg::infra {

    class SFMLVideoRenderer : public core::IVideoRenderer {
    public:
        explicit SFMLVideoRenderer(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<SFMLResourceManager> ressources, std::shared_ptr<float> tileSize);

        void drawSprite(const std::string& spriteId, float x, float y, float size = 1.0f, utils::Color color = {0u,0u,0u,0u}) override;
        void drawRectangle(float x, float y, float width, float height, utils::Color fill, float thickness = 0.0f, utils::Color outline = {0u,0u,0u,0u}) override;
        void drawLine(float x1, float y1, float x2, float y2, float width, utils::Color fill, float thickness = 0.0f, utils::Color outline = {0u,0u,0u,0u}) override;
        void drawCircle(float x, float y, float radius, utils::Color fill, float thickness = 0.0f, utils::Color outline = {0u,0u,0u,0u}) override;

        void drawText(const std::string& text, float size, float x, float y, utils::Color color) override;

        bool isInView(float x, float y) const;

        unsigned int getWindowWidth() const override { return m_window->getSize().x; }
        unsigned int getWindowHeight() const override { return m_window->getSize().y; }

    private:
        std::shared_ptr<sf::RenderWindow> m_window;
        std::shared_ptr<SFMLResourceManager> m_ressources;
        std::shared_ptr<float> m_tileSize;
        sf::Font m_font;
    };

} // namespace tdg::infra

#endif // SFML_VIDEO_RENDERER_HPP
