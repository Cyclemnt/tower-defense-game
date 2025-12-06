#ifndef SFML_RENDERER_HPP
#define SFML_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "infrastructure/interfaces/iRenderer.hpp"

namespace tdg::infra {

    class SFMLRenderer : public IRenderer {
    public:
        explicit SFMLRenderer(sf::RenderWindow& window);

        void beginFrame() override;
        void drawMap(const core::Map&) override;
        void drawCreatures(const std::vector<core::Creature*>&) override;
        void drawTowers(const std::vector<core::Tower*>&) override;
        void endFrame() override;

    private:
        sf::RenderWindow& m_window;
    };

} // namespace tdg::infra

#endif // SFML_RENDERER_HPP