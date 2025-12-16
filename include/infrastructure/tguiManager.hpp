#ifndef TGUI_MANAGER_HPP
#define TGUI_MANAGER_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <chrono>
#include <memory>
#include "core/interfaces/iGuiManager.hpp"
#include "core/interfaces/iVideoRenderer.hpp"

#include "infrastructure/menus/hud.hpp"
#include "infrastructure/menus/towerPanel.hpp"
#include "infrastructure/menus/mainMenu.hpp"
#include "infrastructure/menus/pauseMenu.hpp"
#include "infrastructure/menus/victoryMenu.hpp"
#include "infrastructure/menus/gameOverMenu.hpp"

namespace tdg::infra {

    class TGUIManager : public core::IGUIManager {
    public:
        explicit TGUIManager(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<float> tileSize);

        void processEvent(const sf::Event& event);

        void showMainMenu() override;
        void showHUD() override;
        void showPauseMenu() override;
        void showGameOver() override;
        void showVictory() override;

        void update(float dt) override;
        void render(core::IVideoRenderer& vidRenderer) override;

        void setGameViewProvider(core::GameViewProvider provider) override;

    private:
        std::shared_ptr<tgui::Gui> m_gui{nullptr};
        std::shared_ptr<float> m_tileSize{nullptr};

        std::unique_ptr<HUD> m_hud{nullptr};
        std::unique_ptr<TowerPanel> m_towerPanel{nullptr};

        std::unique_ptr<MainMenu> m_mainMenu{nullptr};
        std::unique_ptr<PauseMenu> m_pauseMenu{nullptr};
        std::unique_ptr<VictoryMenu> m_victoryMenu{nullptr};
        std::unique_ptr<GameOverMenu> m_gameOverMenu{nullptr};
    };

} // namespace tdg::infra

#endif // TGUI_MANAGER_HPP