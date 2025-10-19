#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "menu.hpp"
#include "../game.hpp"
#include "../renderer/renderContext.hpp"

class PauseMenu : public Menu {
public:
    PauseMenu(tgui::Gui& gui, Game& gm, RenderContext& ctx);
    void open() override;
};

#endif // PAUSE_MENU_HPP