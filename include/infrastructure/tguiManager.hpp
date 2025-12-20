#ifndef TGUI_MANAGER_HPP
#define TGUI_MANAGER_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <chrono>
#include <memory>
#include "core/interfaces/iVideoRenderer.hpp"

#include "infrastructure/menus/hud.hpp"
#include "infrastructure/menus/towerPanel.hpp"
#include "infrastructure/menus/mainMenu.hpp"
#include "infrastructure/menus/pauseMenu.hpp"
#include "infrastructure/menus/victoryMenu.hpp"
#include "infrastructure/menus/gameOverMenu.hpp"

namespace tdg::infra {

    class TGUIManager {
    public:
        explicit TGUIManager(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<float> tileSize);

        void processEvent(const sf::Event& event);

        void showMainMenu();
        void showHUD();
        void showPauseMenu();
        void showGameOver();
        void showVictory();

        void update(float dt);
        void renderInGUIView(core::IVideoRenderer& vidRenderer, bool showhu);
        void renderInGameView(core::IVideoRenderer& vidRenderer);

        void setGameViewProvider(core::GameViewProvider provider);

        /* Again, lack of time */
        std::function<void()> m_onAccelerate;
        std::function<void()> m_onNormalSpeed;

        std::function<void()> m_onPause;
        std::function<void()> m_onResume;
        std::function<void()> m_onRestartLevel;
        std::function<void()> m_onQuit;
        std::function<void()> m_onMainMenu;
        std::function<void()> m_onStartStory;
        std::function<void()> m_onStartArcade;
        std::function<void()> m_onNextLevel;

        std::function<void(std::string towerType, int tx,int ty)> onBuildRequest;
        std::function<void(int tx,int ty)> onUpgradeRequest;
        std::function<void(int tx,int ty)> onSellRequest;

        std::function<std::optional<float>(int tx, int ty)> onTowerRangeRequest;
        std::function<bool(std::string towerType)> onCanAffordRequest;
        std::function<bool(int tx, int ty)> onTileOpenRequest;
        std::function<bool(int tx, int ty)> onTowerAtRequest;
        std::function<std::optional<core::Materials>(std::string towerType)> onCostRequest;

        void setCallbacksFurther();
        /* =================== */

    private:
        std::shared_ptr<tgui::Gui> m_gui{nullptr};
        std::shared_ptr<sf::RenderWindow> m_window{nullptr};
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