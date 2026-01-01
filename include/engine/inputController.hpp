// #ifndef INPUT_CONTROLLER_HPP
// #define INPUT_CONTROLLER_HPP

// #include <functional>
// #include <SFML/Graphics.hpp>

// namespace tdg::engine {
    
//     class InputController {
//     public:
//         InputController(/* args */);

//         void processEvent(const sf::Event& event);

//         std::function<void()> onESC;
//         std::function<void(sf::Vector2i)> onLeftDown;
//         std::function<void()> onRightDown;
//         std::function<void()> onLeftUp;
//         std::function<void()> onRightUp;
//         std::function<void()> onWheelClick;
//         std::function<void(sf::Vector2i)> onWheelPan;
//         std::function<void(float)> onWheelScroll;

//     private:
//         bool m_dragging{false};
//         sf::Vector2i m_lastMousePosition{0,0};
//         sf::Vector2i m_viewDeltaPan{0,0};
//         float m_viewDeltaZoom{0.0f};
//     };

// } // namespace tdg::engine

// #endif // INPUT_CONTROLLER_HPP