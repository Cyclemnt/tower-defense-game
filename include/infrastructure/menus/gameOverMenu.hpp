#ifndef GAME_OVER_MENU_HPP
#define GAME_OVER_MENU_HPP

#include <functional>
#include "infrastructure/menus/menu.hpp"

namespace tdg::infra {

    class GameOverMenu final : public Menu {
    public:
        GameOverMenu(std::shared_ptr<tgui::Gui> gui, std::function<void()>& onRestartLevel, std::function<void()>& onMainMenu, std::function<void()>& onQuit);

    private:
        void create() override;

        const std::function<void()>& m_onRestartLevel;
        const std::function<void()>& m_onMainMenu;
        const std::function<void()>& m_onQuit;
    };
};

#endif // GAME_OVER_MENU_HPP