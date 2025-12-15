#include "infrastructure/menus/mainMenu.hpp"

namespace tdg::infra {
    
    MainMenu::MainMenu(std::shared_ptr<tgui::Gui> gui, std::function<void()>& onStartStory, std::function<void()>& onStartArcade, std::function<void()>& onQuit)
        : Menu(gui), m_onStartStory(onStartStory), m_onStartArcade(onStartArcade), m_onQuit(onQuit)
    {
        create();
    }

    void MainMenu::create() {
        sf::Vector2f panelSize = {300.0f, 300.0f};
        sf::Vector2f panelPos = centerPanel(panelSize);

        m_panel = tgui::Panel::create({panelSize});
        m_panel->setPosition({panelPos});
        m_panel->getRenderer()->setBackgroundColor({0, 0, 0, 180});

        auto label = tgui::Label::create("Main Menu");
        label->setTextSize(18);
        label->getRenderer()->setTextColor(tgui::Color::White);
        label->setPosition({10, 10});
        m_panel->add(label);

        auto startStoryBtn = tgui::Button::create("Story");
        startStoryBtn->setSize({"280", "40"});
        startStoryBtn->setPosition({"10", "150"});
        startStoryBtn->onPress([this]() { close(); m_onStartStory(); });
        m_panel->add(startStoryBtn);

        auto startArcadeBtn = tgui::Button::create("Arcade");
        startArcadeBtn->setSize({"280", "40"});
        startArcadeBtn->setPosition({"10", "200"});
        startArcadeBtn->onPress([this]() { close(); m_onStartArcade(); });
        m_panel->add(startArcadeBtn);

        auto quitBtn = tgui::Button::create("Quit");
        quitBtn->setSize({"280", "40"});
        quitBtn->setPosition({"10", "250"});
        quitBtn->onPress([this]() { close(); m_onQuit(); });
        m_panel->add(quitBtn);
    }

} // namespace tdg::infra
