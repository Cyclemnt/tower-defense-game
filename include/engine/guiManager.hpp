#ifndef TGUI_MANAGER_HPP
#define TGUI_MANAGER_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <chrono>
#include <memory>
#include "core/interfaces/iVideoRenderer.hpp"

#include "engine/game.hpp"
#include "engine/commandBus.hpp"

#include "engine/gui/hud.hpp"
#include "engine/gui/towerPanel.hpp"
#include "engine/gui/mainMenu.hpp"
#include "engine/gui/pauseMenu.hpp"
#include "engine/gui/victoryMenu.hpp"
#include "engine/gui/gameOverMenu.hpp"

namespace tdg::engine {

    class TGUIManager {
    public:
        explicit TGUIManager(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<float> tileSize, std::shared_ptr<engine::CommandBus> bus);

        void processEvent(const sf::Event& event);
        void handleLeftClick(sf::Vector2i pixel);
        void handleMouseMove(sf::Vector2i pixel);

        void showMainMenu();
        void setPauseMenu(bool show);
        void showGameOver();
        void showVictory();

        void update(float dt);
        void renderInGUIView(core::IVideoRenderer& vidRenderer, bool showhud);
        void renderInGameView(core::IVideoRenderer& vidRenderer);

        void setGamePtr(std::weak_ptr<Game> game);

    private:
        std::shared_ptr<tgui::Gui> m_gui{nullptr};
        std::shared_ptr<sf::RenderWindow> m_window{nullptr};
        std::shared_ptr<float> m_tileSize{nullptr};

        std::shared_ptr<CommandBus> m_bus;

        std::unique_ptr<HUD> m_hud{nullptr};
        std::unique_ptr<TowerPanel> m_towerPanel{nullptr};
        std::unique_ptr<MainMenu> m_mainMenu{nullptr};
        std::unique_ptr<PauseMenu> m_pauseMenu{nullptr};
        std::unique_ptr<VictoryMenu> m_victoryMenu{nullptr};
        std::unique_ptr<GameOverMenu> m_gameOverMenu{nullptr};
    };

} // namespace tdg::engine

#endif // TGUI_MANAGER_HPP