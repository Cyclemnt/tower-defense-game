#include "engine/inputSystem.hpp"
#include <cmath>

namespace tdg::engine {

    InputSystem::InputSystem(std::shared_ptr<CommandBus> bus)
    : m_bus(bus) {}

    void InputSystem::processEvent(const sf::Event& event) {
        // Key Pressed
        if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
            // ESC
            if (key->code == sf::Keyboard::Key::Escape) {
                Command c{Command::Type::TogglePause};
                m_bus->push(std::move(c));
                return;
            }
        }

        // Mouse Button Pressed
        if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()) {
            // Left
            if (mouse->button == sf::Mouse::Button::Left) {
                Command c{Command::Type::LeftClick, LeftClickPayload{mouse->position}};
                m_bus->push(std::move(c));
                return;
            }
            // Middle
            if (mouse->button == sf::Mouse::Button::Middle) {
                if (!m_dragging) {
                    m_dragStart = mouse->position;
                    m_dragged = false;
                }
                m_dragging = true;
                m_lastMousePosition = mouse->position;
            }
            // Right
            if (mouse->button == sf::Mouse::Button::Right) {
                Command c{Command::Type::setSpeed, setGameSpeedPayload{10.0f}};
                m_bus->push(std::move(c));
            }
        }

        // Mouse Moved
        else if (const auto* mouse = event.getIf<sf::Event::MouseMoved>()) {
            if (m_dragging) {
                if (mouse->position != m_lastMousePosition) m_dragged = true;
                sf::Vector2i delta = mouse->position - m_lastMousePosition;
                Command c{Command::Type::PanView, PanViewPayload{delta}};
                m_bus->push(std::move(c));
                m_lastMousePosition = mouse->position;
            } else {
                Command c{Command::Type::MouseMoved, MouseMovedPayload{mouse->position}};
                m_bus->push(std::move(c));
            }
        }

        // Mouse Wheel Scrolled
        else if (const auto* mouse = event.getIf<sf::Event::MouseWheelScrolled>()) {
            float zoomFactor = 1.0f + mouse->delta * 0.1f;
            sf::Vector2i zoomFocus = mouse->position;
            Command c{Command::Type::ZoomView, ZoomViewPayload{zoomFactor, zoomFocus}};
            m_bus->push(std::move(c));
        }

        // Mouse Button Released
        else if (const auto* mouse = event.getIf<sf::Event::MouseButtonReleased>()) {
            // Middle
            if (mouse->button == sf::Mouse::Button::Middle) {
                m_dragging = false;
                if (!m_dragged) {
                    Command c{Command::Type::ResetView};
                    m_bus->push(std::move(c));
                }
            }
            // Right
            if (mouse->button == sf::Mouse::Button::Right) {
                Command c{Command::Type::setSpeed, setGameSpeedPayload{1.0f}};
                m_bus->push(std::move(c));
            }
        }
    }

} // namespace tdg::engine