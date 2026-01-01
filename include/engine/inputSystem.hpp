#ifndef INPUT_SYSTEM_HPP
#define INPUT_SYSTEM_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "engine/commandBus.hpp"
#include "engine/command.hpp"

namespace tdg::engine {

    class InputSystem {
    public:
        InputSystem(std::shared_ptr<CommandBus> bus);

        void processEvent(const sf::Event& ev);

    private:
        std::shared_ptr<CommandBus> m_bus;

        // Drag state
        bool m_dragging{false};
        bool m_dragged{false};
        sf::Vector2i m_dragStart{};
        sf::Vector2i m_lastMousePosition{};
    };

}

#endif // INPUT_SYSTEM_HPP