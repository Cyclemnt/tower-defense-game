#ifndef SFML_VIDEO_RENDERER_HPP
#define SFML_VIDEO_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "infrastructure/interfaces/iVideoRenderer.hpp"
#include "infrastructure/sfmlResourceManager.hpp"

namespace tdg::infra {

    class SFMLVideoRenderer : public IVideoRenderer {
    public:
        explicit SFMLVideoRenderer(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<SFMLResourceManager> ressources, std::shared_ptr<float> tileSize);

        void drawSprite(const std::string& spriteId, float x, float y) override;
        void drawRectangle(float x, float y, float width, float height, int red, int green, int blue, int alpha) override;
        void drawRectangle(float x1, float y1, float x2, float y2, float width, int red, int green, int blue, int alpha) override;
        void drawCircle(float x, float y, float radius, int red, int green, int blue, int alpha) override;

        bool isInView(float x, float y) const;

    private:
        std::shared_ptr<sf::RenderWindow> m_window;
        std::shared_ptr<SFMLResourceManager> m_ressources;
        std::shared_ptr<float> m_tileSize;
    };

} // namespace tdg::infra

#endif // SFML_VIDEO_RENDERER_HPP
