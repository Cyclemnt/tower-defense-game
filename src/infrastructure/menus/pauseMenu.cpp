#include "infrastructure/menus/pauseMenu.hpp"

namespace tdg::infra {
    
    PauseMenu::PauseMenu(std::shared_ptr<tgui::Gui> gui, std::function<void()>& onResume, std::function<void()>& onRestart, std::function<void()>& onMainMenu, std::function<void()>& onQuit)
        : Menu(gui), m_onResume(onResume), m_onRestartLevel(onRestart), m_onMainMenu(onMainMenu), m_onQuit(onQuit)
    {
        create();
    }

    void PauseMenu::create() {
        sf::Vector2f panelSize = {300.0f, 300.0f};
        sf::Vector2f panelPos = centerPanel(panelSize);

        m_panel = tgui::Panel::create({panelSize});
        m_panel->setPosition({panelPos});
        m_panel->getRenderer()->setBackgroundColor({0, 0, 0, 180});

        auto label = tgui::Label::create("Game Paused");
        label->setTextSize(18);
        label->getRenderer()->setTextColor(tgui::Color::White);
        label->setPosition({10, 10});
        m_panel->add(label);

        auto resumeBtn = tgui::Button::create("Resume");
        resumeBtn->setSize({"280", "40"});
        resumeBtn->setPosition({"10", "150"});
        resumeBtn->onPress([this]() { close(); m_onResume(); });
        m_panel->add(resumeBtn);

        auto restartLevelBtn = tgui::Button::create("Restart");
        restartLevelBtn->setSize({"280", "40"});
        restartLevelBtn->setPosition({"10", "200"});
        restartLevelBtn->onPress([this]() { close(); m_onRestartLevel(); });
        m_panel->add(restartLevelBtn);

        auto mainMenuBtn = tgui::Button::create("Main Menu");
        mainMenuBtn->setSize({"280", "40"});
        mainMenuBtn->setPosition({"10", "250"});
        mainMenuBtn->onPress([this]() { close(); m_onMainMenu(); });
        m_panel->add(mainMenuBtn);

        auto quitBtn = tgui::Button::create("Quit");
        quitBtn->setSize({"280", "40"});
        quitBtn->setPosition({"10", "250"});
        quitBtn->onPress([this]() { close(); m_onQuit(); });
        m_panel->add(quitBtn);
    }

} // namespace tdg::infra
