#include "infrastructure/menus/gameOverMenu.hpp"

namespace tdg::infra {
    
    GameOverMenu::GameOverMenu(std::shared_ptr<tgui::Gui> gui, std::function<void()>& onRestartLevel, std::function<void()>& onMainMenu, std::function<void()>& onQuit)
        : Menu(gui), m_onRestartLevel(onRestartLevel), m_onMainMenu(onMainMenu), m_onQuit(onQuit)
    {
        create();
    }

    void GameOverMenu::create() {
        sf::Vector2f panelSize = {300.0f, 250.0f};
        sf::Vector2f panelPos = centerPanel(panelSize);

        m_panel = tgui::Panel::create({panelSize});
        m_panel->setPosition({panelPos});
        m_panel->getRenderer()->setBackgroundColor({0, 0, 0, 180});

        auto label = tgui::Label::create("Game Over");
        label->setTextSize(18);
        label->getRenderer()->setTextColor(tgui::Color::White);
        label->setPosition({10, 10});
        m_panel->add(label);

        auto restartLevelBtn = tgui::Button::create("Restart Level");
        restartLevelBtn->setSize({"280", "40"});
        restartLevelBtn->setPosition({"10", "100"});
        restartLevelBtn->onPress([this]() { close(); m_onRestartLevel(); });
        m_panel->add(restartLevelBtn);

        auto mainMenuBtn = tgui::Button::create("Main Menu");
        mainMenuBtn->setSize({"280", "40"});
        mainMenuBtn->setPosition({"10", "150"});
        mainMenuBtn->onPress([this]() { close(); m_onMainMenu(); });
        m_panel->add(mainMenuBtn);

        auto quitBtn = tgui::Button::create("Quit");
        quitBtn->setSize({"280", "40"});
        quitBtn->setPosition({"10", "200"});
        quitBtn->onPress([this]() { close(); m_onQuit(); });
        m_panel->add(quitBtn);

    }

} // namespace tdg::infra
