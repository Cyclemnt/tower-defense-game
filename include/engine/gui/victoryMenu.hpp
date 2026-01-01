#ifndef VICTORY_MENU_HPP
#define VICTORY_MENU_HPP

#include <functional>
#include "engine/gui/menu.hpp"
#include "engine/commandBus.hpp"

namespace tdg::engine {

    class VictoryMenu final : public Menu {
    public:
        VictoryMenu(std::shared_ptr<tgui::Gui> gui, std::shared_ptr<CommandBus> bus);

    private:
        void create() override;
        
        std::shared_ptr<CommandBus> m_bus;
    };

}; // namespace tdg::engine

#endif // VICTORY_MENU_HPP