#ifndef VIEW_MANAGER_HPP
#define VIEW_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <memory>

namespace tdg::engine {

    class ViewManager {
    public:
        enum class View { Game, GUI };

        ViewManager(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<float> tileSize);

        void resetGameView(unsigned int mapW, unsigned int mapH);

        // delta in pixels (mouse movement)
        void panGameView(sf::Vector2i delta);

        // factor > 1 => zoom in
        // focus = mouse position in window pixels
        void zoomGameView(float factor, sf::Vector2i focus);

        void setView(ViewManager::View view);

    private:
        void clampGameView();
        void recomputeZoomLimits();

    private:
        std::shared_ptr<sf::RenderWindow> m_window{nullptr};
        std::shared_ptr<float> m_tileSize{nullptr};

        sf::View m_guiView;
        sf::View m_gameView;

        sf::Vector2f m_offset;

        sf::Vector2i m_mapSizeTiles{0,0};
        sf::Vector2f m_mapSizePx{0.0f, 0.0f};

        int m_paddingTiles{5};

        float m_zoomLevel{1.0f};
        float m_minZoom{0.25f};
        float m_maxZoom{1.0f};
    };

} // namespace tdg::engine

#endif // VIEW_MANAGER_HPP
