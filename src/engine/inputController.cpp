// #include "engine/inputController.hpp"

// namespace tdg::engine {

//     InputController::InputController() {}

//     void InputController::processEvent(const sf::Event& event) {
//         // Key Pressed
//         if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
//             if (key->code == sf::Keyboard::Key::Escape) {
//                 onESC(); // toggle pause and pause menu
//             }
//         }

//         // Mouse Button Pressed
//         if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()) {
//             if (mouse->button == sf::Mouse::Button::Left) {
//                 // Check if click on towerpanel (if so consume click)
//                 // Check for tile click
//                 onLeftDown(mouse->position);
//             }
//             if (mouse->button == sf::Mouse::Button::Middle) {
//                 m_dragging = true;
//                 m_lastMousePosition = mouse->position;
//             }
//             if (mouse->button == sf::Mouse::Button::Right) {
//                 onRightDown(); // Accelerate game
//             }
//         }
//         // Mouse Button Released
//         else if (const auto* mouse = event.getIf<sf::Event::MouseButtonReleased>()) {
//             if (mouse->button == sf::Mouse::Button::Middle) {
//                 m_dragging = false;
//                 if (m_lastMousePosition == mouse->position) {
//                     onWheelClick(); // Reset "game" window view
//                 }
//             }
//             if (mouse->button == sf::Mouse::Button::Right) {
//                 onRightUp(); // Reset game speed
//             }
//         }
//         // Mouse Moved
//         else if (const auto* mouse = event.getIf<sf::Event::MouseMoved>()) {
//             // Update tile & tower overlays
//             if (m_dragging) {
//                 m_viewDeltaPan = mouse->position - m_lastMousePosition;
//                 onWheelPan(m_viewDeltaPan);
//                 m_lastMousePosition = mouse->position;
//             }
//         }
//         // Mouse Wheel Scrolled
//         else if (const auto* mouse = event.getIf<sf::Event::MouseWheelScrolled>()) {
//             m_viewDeltaZoom = 1.0f + mouse->delta * 0.1f;
//             onWheelScroll(m_viewDeltaZoom); // Zoom/UnZoom "game" window view
//         }
//     }
    
// } // namespace tdg::engine
