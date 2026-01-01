#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include <functional>
#include "engine/gui/menu.hpp"
#include "engine/commandBus.hpp"

namespace tdg::engine {

    class PauseMenu final : public Menu {
    public:
        PauseMenu(std::shared_ptr<tgui::Gui> gui, std::shared_ptr<CommandBus> bus);

    private:
        void create() override;
        
        std::shared_ptr<CommandBus> m_bus;
    };
}; // namespace tdg::engine

#endif // PAUSE_MENU_HPP