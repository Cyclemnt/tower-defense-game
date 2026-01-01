#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <functional>
#include "engine/gui/menu.hpp"
#include "engine/commandBus.hpp"

namespace tdg::engine {

    class MainMenu final : public Menu {
    public:
        MainMenu(std::shared_ptr<tgui::Gui> gui, std::shared_ptr<CommandBus> bus);

    private:
        void create() override;
        
        std::shared_ptr<CommandBus> m_bus;
    };
}; // namespace tdg::engine

#endif // MAIN_MENU_HPP