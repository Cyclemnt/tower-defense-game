#include "../../include/gui/cameraController.hpp"
#include "../../include/renderer/renderer.hpp"
#include <algorithm>

CameraController::CameraController(RenderContext& ctx_)
    : ctx(ctx_) {}

void CameraController::handleZoom(const sf::Event& event) {
    if (const auto* mouse = event.getIf<sf::Event::MouseWheelScrolled>()) {
        float factor = 1.0f + mouse->delta * zoomSpeed;
        if (factor == 0.0f) return;

        const float oldSize = ctx.tileSize;
        ctx.tileSize = std::clamp(ctx.tileSize * factor, minTileSize, maxTileSize);

        const sf::Vector2i mousePos = mouse->position;
        const sf::Vector2f mouseGridBefore = (static_cast<sf::Vector2f>(mousePos) - ctx.offset) / oldSize;

        ctx.offset = static_cast<sf::Vector2f>(mousePos) - mouseGridBefore * ctx.tileSize;
    }
}

void CameraController::handleDrag(const sf::Event& event) {
    if (const auto* press = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (press->button == sf::Mouse::Button::Left) {
            dragging = true;
            lastMousePos = press->position;
        }
    } else if (const auto* release = event.getIf<sf::Event::MouseButtonReleased>()) {
        if (release->button == sf::Mouse::Button::Left)
            dragging = false;
    } else if (const auto* move = event.getIf<sf::Event::MouseMoved>()) {
        if (dragging) {
            const sf::Vector2i delta = move->position - lastMousePos;
            ctx.offset += sf::Vector2f(static_cast<float>(delta.x), static_cast<float>(delta.y));
            lastMousePos = move->position;
        }
    }
}

void CameraController::resetView() {
    ctx.renderer.computeScaling();
}
