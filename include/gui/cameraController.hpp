#ifndef CAMERA_CONTROLLER_HPP
#define CAMERA_CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include "../renderer/renderContext.hpp"

/**
 * @brief Handles camera movement (panning and zooming) based on user input.
 * 
 * This class modifies the RenderContext offset and tile size to simulate
 * a movable and zoomable camera over the map.
 */
class CameraController {
private:
    RenderContext& ctx;
    bool isDragging = false;
    sf::Vector2i lastMousePos;

    // Zoom parameters
    const float minTileSize = 24.0f;
    const float maxTileSize = 196.0f;
    const float zoomSpeed = 0.1f; // Zoom factor per wheel step

public:
    explicit CameraController(RenderContext& ctx);

    void handleZoom(const sf::Event& event);
    void handleDrag(const sf::Event& event);
    void resetView(); // re-center and reset zoom
};

#endif // CAMERA_CONTROLLER_HPP
