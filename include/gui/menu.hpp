#ifndef MENU_HPP
#define MENU_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "../game.hpp"
#include "../renderer/renderContext.hpp"

class Menu {
protected:
    tgui::Gui& gui;
    Game& game;
    RenderContext& ctx;
    tgui::Panel::Ptr panel;
    bool on = false;

    // Utility: center a panel of given size
    sf::Vector2f centerPanel(float w, float h) const;

public:
    Menu(tgui::Gui& g, Game& gm, RenderContext& c);
    virtual ~Menu() = default;

    virtual void open() = 0;  // each menu builds its own widgets
    virtual void close();

    bool isOn() const { return on; }
};

#endif // MENU_HPP