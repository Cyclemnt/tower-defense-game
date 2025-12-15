#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <functional>
#include "infrastructure/menus/menu.hpp"

namespace tdg::infra {

    class MainMenu final : public Menu {
    public:
        MainMenu(std::shared_ptr<tgui::Gui> gui, std::function<void()>& onStartStory, std::function<void()>& onStartArcade, std::function<void()>& onQuit);

    private:
        void create() override;

        const std::function<void()>& m_onStartStory;
        const std::function<void()>& m_onStartArcade;
        const std::function<void()>& m_onQuit;
    };
};

#endif // MAIN_MENU_HPP