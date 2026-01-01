#include "engine/gui/menu.hpp"

namespace tdg::engine {

    Menu::Menu(std::shared_ptr<tgui::Gui> gui) : m_gui(gui) {}

    void Menu::show() noexcept {
        m_gui->add(m_panel);
    }

    void Menu::close() noexcept {
        if (m_panel) m_gui->remove(m_panel);
    }

    sf::Vector2f Menu::centerPanel(const sf::Vector2f& size) const noexcept {
        sf::Vector2u win = {m_gui->getWindow()->getSize()};
        sf::Vector2f pos = (static_cast<sf::Vector2f>(win) - size) * 0.5f;
        return pos;
    }
    
} // namespace tdg::engine
