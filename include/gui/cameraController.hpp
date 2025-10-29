#ifndef CAMERA_CONTROLLER_HPP
#define CAMERA_CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include "../renderer/renderContext.hpp"

/**
 * @class CameraController
 * @brief Manages camera movement and zoom in the world view.
 *
 * This modifies the RenderContext offset and tile size to simulate
 * a dynamic camera controlled by the user.
 */
class CameraController final {
private:
    RenderContext& ctx;
    bool dragging = false;
    sf::Vector2i lastMousePos;

    const float minTileSize = 24.0f;
    const float maxTileSize = 196.0f;
    const float zoomSpeed = 0.1f;

public:
    explicit CameraController(RenderContext& ctx_);

    /// @brief Handles mouse wheel zooming.
    void handleZoom(const sf::Event& event);

    /// @brief Handles mouse dragging for camera panning.
    void handleDrag(const sf::Event& event);

    /// @brief Resets camera view to default scale and centering.
    void resetView();
};

#endif // CAMERA_CONTROLLER_HPP
