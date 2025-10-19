#include "../../include/gui/menu.hpp"

Menu::Menu(tgui::Gui& g, Game& gm, RenderContext& c)
    : gui(g), game(gm), ctx(c) {}

sf::Vector2f Menu::centerPanel(float w, float h) const {
    sf::Vector2u win = ctx.window.getSize();
    return { (win.x - w) * 0.5f, (win.y - h) * 0.5f };
}

void Menu::close() {
    if (panel) {
        gui.remove(panel);
        panel.reset();
    }
    on = false;
}
