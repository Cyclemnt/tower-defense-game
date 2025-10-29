#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include "menu.hpp"

/**
 * @class PauseMenu
 * @brief Simple pause menu with resume (and optionally other actions).
 */
class PauseMenu final : public Menu {
public:
    PauseMenu(tgui::Gui& gui, Game& game, const RenderContext& ctx) noexcept;
    void open() override;
};

#endif // PAUSE_MENU_HPP
