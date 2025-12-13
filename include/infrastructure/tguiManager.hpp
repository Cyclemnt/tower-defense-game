#ifndef TGUI_MANAGER_HPP
#define TGUI_MANAGER_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <chrono>
#include <memory>
#include "infrastructure/interfaces/iGuiManager.hpp"

namespace tdg::infra {

    class TGUIManager : public IGUIManager {
    public:
        explicit TGUIManager(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<float> tileSize);

        void showMainMenu() override;
        void showHUD() override;
        void showPauseMenu() override;
        void showGameOver() override;
        void showVictory() override;

        void update(float dt) override;
        void render() override;

    private:
        std::unique_ptr<tgui::Gui> m_gui;
        std::shared_ptr<float> m_tileSize;
    };

} // namespace tdg::infra

#endif // TGUI_MANAGER_HPP