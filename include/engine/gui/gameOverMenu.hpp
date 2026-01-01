#ifndef GAME_OVER_MENU_HPP
#define GAME_OVER_MENU_HPP

#include <functional>
#include "engine/gui/menu.hpp"
#include "engine/commandBus.hpp"

namespace tdg::engine {

    class GameOverMenu final : public Menu {
    public:
        GameOverMenu(std::shared_ptr<tgui::Gui> gui, std::shared_ptr<CommandBus> bus);

    private:
        void create() override;
        
        std::shared_ptr<CommandBus> m_bus;
    };
}; // namespace tdg::engine

#endif // GAME_OVER_MENU_HPP