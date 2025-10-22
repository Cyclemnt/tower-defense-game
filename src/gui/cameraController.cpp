#include <algorithm>
#include "../../include/gui/cameraController.hpp"
#include "../../include/renderer/renderer.hpp"

CameraController::CameraController(RenderContext& ctx)
    : ctx(ctx) {}

void CameraController::handleZoom(const sf::Event& event) {
    if (auto mouse = event.getIf<sf::Event::MouseWheelScrolled>()) {
        // Compute new zoom factor
        float factor = 1.0f + mouse->delta * zoomSpeed;
        if (factor == 0.0f) return;

        float oldTileSize = ctx.tileSize;
        ctx.tileSize *= factor;
        ctx.tileSize = std::clamp(ctx.tileSize, minTileSize, maxTileSize);

        // Mouse position (in window space)
        sf::Vector2i mousePos = mouse->position;

        // Mouse position in map grid coordinates before zoom
        sf::Vector2f mouseGridPos = {
            (mousePos.x - ctx.offset.x) / oldTileSize,
            (mousePos.y - ctx.offset.y) / oldTileSize
        };

        // Adjust offset to keep zoom centered around mouse cursor
        ctx.offset.x = mousePos.x - mouseGridPos.x * ctx.tileSize;
        ctx.offset.y = mousePos.y - mouseGridPos.y * ctx.tileSize;
    }
}

void CameraController::handleDrag(const sf::Event& event) {
    // Mouse button pressed, start dragging
    if (auto mb = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mb->button == sf::Mouse::Button::Left) {
            isDragging = true;
            lastMousePos = mb->position;
        }
    }
    // Mouse button released, stop dragging
    else if (auto mr = event.getIf<sf::Event::MouseButtonReleased>()) {
        if (mr->button == sf::Mouse::Button::Left) {
            isDragging = false;
        }
    }
    // Mouse moved, update offset while dragging
    else if (auto mm = event.getIf<sf::Event::MouseMoved>()) {
        if (isDragging) {
            sf::Vector2i newPos = { mm->position.x, mm->position.y };
            sf::Vector2i delta = newPos - lastMousePos;

            ctx.offset.x += static_cast<float>(delta.x);
            ctx.offset.y += static_cast<float>(delta.y);

            lastMousePos = newPos;
        }
    }
}


void CameraController::resetView() {
    ctx.renderer.computeScaling();
}
