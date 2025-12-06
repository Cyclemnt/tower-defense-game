#ifndef TGUI_MANAGER_HPP
#define TGUI_MANAGER_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <chrono>
#include "infrastructure/interfaces/iGuiManager.hpp"

namespace tdg::infra {

    class TGUIGUIManager : public IGUIManager {
    public:
        explicit TGUIGUIManager(tgui::Gui& gui);

        void showMainMenu() override;
        void showHUD() override;
        void showPauseMenu() override;
        void showGameOver() override;
        void showVictory() override;

        void update(std::chrono::milliseconds dt) override;
        void render() override;

    private:
        tgui::Gui& m_gui;
    };

} // namespace tdg::infra

#endif // TGUI_MANAGER_HPP