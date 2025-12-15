#ifndef MENU_HPP
#define MENU_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <memory>

namespace tdg::infra {
    
    class Menu {
    public:
        Menu(std::shared_ptr<tgui::Gui> gui);
        virtual ~Menu() = default;

        virtual void show() noexcept;
        
    protected:
        virtual void create() = 0;

        void close() noexcept;
        sf::Vector2f centerPanel(const sf::Vector2f& size) const noexcept;

        std::shared_ptr<tgui::Gui> m_gui;
        tgui::Panel::Ptr m_panel;
    };

} // namespace tdg::infra

#endif // MENU_HPP