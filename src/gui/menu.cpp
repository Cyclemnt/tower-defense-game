#include "../../include/gui/menu.hpp"

Menu::Menu(tgui::Gui& gui_, Game& game_, const RenderContext& ctx_) noexcept
    : gui(gui_), game(game_), ctx(ctx_) {}

sf::Vector2f Menu::centerPanel(const sf::Vector2f& size) const noexcept {
    sf::Vector2u win = {ctx.window.getSize()};
    sf::Vector2f pos = (static_cast<sf::Vector2f>(win) - size) * 0.5f;
    return pos;
}

void Menu::close() noexcept {
    if (panel) gui.remove(panel);
    on = false;
}
