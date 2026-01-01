#include <algorithm>
#include <cmath>
#include "engine/viewManager.hpp"

namespace tdg::engine {

    ViewManager::ViewManager(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<float> tileSize)
        : m_tileSize(tileSize), m_window(window)
    {
        // GUI view always matches window size
        m_guiView = sf::View(sf::FloatRect({0.0f, 0.0f}, {static_cast<sf::Vector2f>(m_window->getSize())}));
    }

    void ViewManager::recomputeZoomLimits() {
        if (!m_tileSize || *m_tileSize <= 0.0f) return;
        if (m_mapSizePx.x <= 0.0f || m_mapSizePx.y <= 0.0f) return;

        sf::Vector2f winSize = static_cast<sf::Vector2f>(m_window->getSize());
        float paddingPx = static_cast<float>(m_paddingTiles) * (*m_tileSize);

        // Max zoom allowed so the view never exceeds map + padding
        float maxZoomX = (m_mapSizePx.x + 2.0f * paddingPx) / winSize.x;
        float maxZoomY = (m_mapSizePx.y + 2.0f * paddingPx) / winSize.y;

        m_maxZoom = std::min(maxZoomX, maxZoomY);

        // Keep zoom interval valid
        if (m_minZoom > m_maxZoom) m_minZoom = m_maxZoom;
    }

    void ViewManager::resetGameView(unsigned int mapW, unsigned int mapH) {
        const sf::Vector2i mapSize(mapW, mapH);
        sf::Vector2f winSize = static_cast<sf::Vector2f>(m_window->getSize());

        // Compute largest tile size fitting the map in the window
        float maxTileSizeX = winSize.x / (mapSize.x + 2);
        float maxTileSizeY = winSize.y / (mapSize.y + 2);
        float newTileSize = std::min(maxTileSizeX, maxTileSizeY);

        *m_tileSize = newTileSize;

        // Map size in tiles and pixels
        m_mapSizeTiles = mapSize;
        m_mapSizePx = static_cast<sf::Vector2f>(mapSize) * (*m_tileSize);

        // Base view matches window size
        m_gameView = sf::View(sf::FloatRect({0.0f, 0.0f}, {winSize.x, winSize.y}));
        m_gameView.setCenter(m_mapSizePx * 0.5f);

        // Compute zoom bounds from map + padding
        recomputeZoomLimits();

        // Start at the farthest allowed zoom-out
        m_zoomLevel = m_maxZoom;
        if (std::abs(m_zoomLevel - 1.0f) > 1e-6f) m_gameView.zoom(m_zoomLevel);

        clampGameView();
    }

    void ViewManager::panGameView(sf::Vector2i delta) {
        if (delta == sf::Vector2i(0,0)) return;

        sf::Vector2f winSize = static_cast<sf::Vector2f>(m_window->getSize());
        sf::Vector2f viewSize = m_gameView.getSize();

        // Convert pixel delta to world delta (depends on zoom)
        sf::Vector2f worldDelta(
            delta.x * (viewSize.x / winSize.x),
            delta.y * (viewSize.y / winSize.y)
        );

        // Move opposite to mouse drag
        m_gameView.move(-worldDelta);
        clampGameView();
    }

    void ViewManager::zoomGameView(float factor, sf::Vector2i focus) {
        if (factor <= 0.0f) return;

        // factor > 1 => zoom in (reduce zoom level)
        float targetZoom = m_zoomLevel / factor;
        targetZoom = std::clamp(targetZoom, m_minZoom, m_maxZoom);

        float actualFactor = targetZoom / m_zoomLevel;
        if (std::abs(actualFactor - 1.0f) < 1e-6f) return;

        // World position under cursor before zoom
        sf::Vector2f before = m_window->mapPixelToCoords(focus, m_gameView);

        m_gameView.zoom(actualFactor);
        m_zoomLevel = targetZoom;

        // World position under cursor after zoom
        sf::Vector2f after = m_window->mapPixelToCoords(focus, m_gameView);

        // Move the view
        m_gameView.move(before - after);

        clampGameView();
    }

    void ViewManager::setView(ViewManager::View view) {
        switch (view) {
            case ViewManager::View::Game: m_window->setView(m_gameView); break;
            case ViewManager::View::GUI:  m_window->setView(m_guiView);  break;
            default: break;
        }
    }

    void ViewManager::clampGameView() {
        if (!m_tileSize || *m_tileSize <= 0.0f) return;

        float paddingPx = static_cast<float>(m_paddingTiles) * (*m_tileSize);

        sf::Vector2f viewSize = m_gameView.getSize();
        sf::Vector2f half = viewSize * 0.5f;
        sf::Vector2f center = m_gameView.getCenter();

        // Clamp X axis
        if (m_mapSizePx.x + 2.0f * paddingPx <= viewSize.x) {
            center.x = m_mapSizePx.x * 0.5f;
        } else {
            center.x = std::clamp(center.x, -paddingPx + half.x, m_mapSizePx.x + paddingPx - half.x);
        }

        // Clamp Y axis
        if (m_mapSizePx.y + 2.0f * paddingPx <= viewSize.y) {
            center.y = m_mapSizePx.y * 0.5f;
        } else {
            center.y = std::clamp(center.y, -paddingPx + half.y, m_mapSizePx.y + paddingPx - half.y);
        }

        m_gameView.setCenter(center);
    }

} // namespace tdg::engine
