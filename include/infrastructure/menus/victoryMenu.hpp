#ifndef VICTORY_MENU_HPP
#define VICTORY_MENU_HPP

#include <functional>
#include "infrastructure/menus/menu.hpp"

namespace tdg::infra {

    class VictoryMenu final : public Menu {
    public:
        VictoryMenu(std::shared_ptr<tgui::Gui> gui, std::function<void()>& onNextLevel, std::function<void()>& onRestartLevel, std::function<void()>& onMainMenu, std::function<void()>& onQuit);

    private:
        void create() override;

        const std::function<void()>& m_onNextLevel;
        const std::function<void()>& m_onRestartLevel;
        const std::function<void()>& m_onMainMenu;
        const std::function<void()>& m_onQuit;
    };
};

#endif // VICTORY_MENU_HPP