#include "infrastructure/menus/victoryMenu.hpp"

namespace tdg::infra {
    
    VictoryMenu::VictoryMenu(std::shared_ptr<tgui::Gui> gui, std::function<void()>& onNextLevel, std::function<void()>& onRestartLevel, std::function<void()>& onMainMenu, std::function<void()>& onQuit)
        : Menu(gui), m_onNextLevel(onNextLevel), m_onRestartLevel(onRestartLevel), m_onMainMenu(onMainMenu), m_onQuit(onQuit)
    {
        create();
    }

    void VictoryMenu::create() {
        sf::Vector2f panelSize = {300.0f, 350.0f};
        sf::Vector2f panelPos = centerPanel(panelSize);

        m_panel = tgui::Panel::create({panelSize});
        m_panel->setPosition({panelPos});
        m_panel->getRenderer()->setBackgroundColor({0, 0, 0, 180});

        auto label = tgui::Label::create("Victory");
        label->setTextSize(18);
        label->getRenderer()->setTextColor(tgui::Color::White);
        label->setPosition({10, 10});
        m_panel->add(label);

        auto nextLevelBtn = tgui::Button::create("Next Level");
        nextLevelBtn->setSize({"280", "40"});
        nextLevelBtn->setPosition({"10", "150"});
        nextLevelBtn->onPress([this]() { close(); m_onNextLevel(); });
        m_panel->add(nextLevelBtn);

        auto restartLevelBtn = tgui::Button::create("Restart Level");
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
        quitBtn->setPosition({"10", "300"});
        quitBtn->onPress([this]() { close(); m_onQuit(); });
        m_panel->add(quitBtn);

    }

} // namespace tdg::infra
