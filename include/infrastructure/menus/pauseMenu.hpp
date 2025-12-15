#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include <functional>
#include "infrastructure/menus/menu.hpp"

namespace tdg::infra {

    class PauseMenu final : public Menu {
    public:
        PauseMenu(std::shared_ptr<tgui::Gui> gui, std::function<void()>& onResume, std::function<void()>& onRestart, std::function<void()>& onMainMenu, std::function<void()>& onQuit);

    private:
        void create() override;

        const std::function<void()>& m_onResume;
        const std::function<void()>& m_onRestartLevel;
        const std::function<void()>& m_onMainMenu;
        const std::function<void()>& m_onQuit;
    };
};

#endif // PAUSE_MENU_HPP