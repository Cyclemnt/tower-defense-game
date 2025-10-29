#ifndef MENU_HPP
#define MENU_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "../game.hpp"
#include "../renderer/renderContext.hpp"

/**
 * @class Menu
 * @brief Lightweight base class for TGUI menus (panel-centered).
 *
 * Provides common helpers for derived menus (centering, open/close).
 * Derived classes should implement open() to build widgets.
 */
class Menu {
protected:
    tgui::Gui& gui;
    Game& game;
    const RenderContext& ctx;
    tgui::Panel::Ptr panel;    ///< Main panel widget
    bool on = false;           ///< Is currently shown?

    /// @brief Compute position to center a panel of given size in the window.
    [[nodiscard]] sf::Vector2f centerPanel(const sf::Vector2f& size) const noexcept;

public:
    Menu(tgui::Gui& gui_, Game& game_, const RenderContext& ctx_) noexcept;
    virtual ~Menu() = default;

    /// @brief Build and show the menu widgets.
    virtual void open() = 0;

    /// @brief Close the menu and remove widgets.
    virtual void close() noexcept;

    [[nodiscard]] bool isOn() const noexcept { return on; }
};

#endif // MENU_HPP
