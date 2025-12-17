#include "infrastructure/menus/mainMenu.hpp"

namespace tdg::infra {
    
    MainMenu::MainMenu(std::shared_ptr<tgui::Gui> gui, std::function<void()>& onStartStory, std::function<void()>& onStartArcade, std::function<void()>& onQuit)
        : Menu(gui), m_onStartStory(onStartStory), m_onStartArcade(onStartArcade), m_onQuit(onQuit)
    {
        create();
    }

    void MainMenu::create() {
        // sf::Vector2f panelSize = {300.0f, 300.0f};
        // sf::Vector2f panelPos = centerPanel(panelSize);

        // m_panel = tgui::Panel::create({panelSize});
        // m_panel->setPosition({panelPos});
        // m_panel->getRenderer()->setBackgroundColor({0, 0, 0, 180});

        // auto label = tgui::Label::create("Main Menu");
        // label->setTextSize(18);
        // label->getRenderer()->setTextColor(tgui::Color::White);
        // label->setPosition({10, 10});
        // m_panel->add(label);

        // auto startStoryBtn = tgui::Button::create("Story");
        // startStoryBtn->setSize({"280", "40"});
        // startStoryBtn->setPosition({"10", "150"});
        // startStoryBtn->onPress([this]() { close(); m_onStartStory(); });
        // m_panel->add(startStoryBtn);

        // auto startArcadeBtn = tgui::Button::create("Arcade");
        // startArcadeBtn->setSize({"280", "40"});
        // startArcadeBtn->setPosition({"10", "200"});
        // startArcadeBtn->onPress([this]() { close(); m_onStartArcade(); });
        // m_panel->add(startArcadeBtn);

        // auto quitBtn = tgui::Button::create("Quit");
        // quitBtn->setSize({"280", "40"});
        // quitBtn->setPosition({"10", "250"});
        // quitBtn->onPress([this]() { close(); m_onQuit(); });
        // m_panel->add(quitBtn);


        sf::Vector2f panelSize = {1920.0f, 1190.0f};
        sf::Vector2f panelPos = centerPanel(panelSize);

        m_panel = tgui::Panel::create({panelSize});
        m_panel->setPosition({panelPos});
        m_panel->getRenderer()->setBackgroundColor({0, 0, 0, 0});

        auto label = tgui::Label::create("Main Menu");
        label->setTextSize(18);
        // label->getRenderer()->setTextColor(tgui::Color::White);
        label->setPosition({10, 10});
        // m_panel->add(label);

        auto startStoryBtn = tgui::Button::create("");
        startStoryBtn->setSize({"440", "145"});
        startStoryBtn->setPosition({"195", "893"});
        startStoryBtn->getRenderer()->setBackgroundColor({0,0,0,0});
        startStoryBtn->getRenderer()->setBorderColor({0,0,0,0});
        startStoryBtn->getRenderer()->setBackgroundColorHover({0,0,0,0});
        startStoryBtn->getRenderer()->setBorderColorHover({0,0,0,0});
        startStoryBtn->getRenderer()->setBackgroundColorDown({0,0,0,0});
        startStoryBtn->getRenderer()->setBorderColorDown({0,0,0,0});
        startStoryBtn->onPress([this]() { close(); m_onStartStory(); });
        m_panel->add(startStoryBtn);

        auto startArcadeBtn = tgui::Button::create("");
        startArcadeBtn->setSize({"410", "145"});
        startArcadeBtn->setPosition({"755", "893"});
        startArcadeBtn->getRenderer()->setBackgroundColor({0,0,0,0});
        startArcadeBtn->getRenderer()->setBorderColor({0,0,0,0});
        startArcadeBtn->getRenderer()->setBackgroundColorHover({0,0,0,0});
        startArcadeBtn->getRenderer()->setBorderColorDownHover({0,0,0,0});
        startArcadeBtn->getRenderer()->setBorderColorHover({0,0,0,0});
        startArcadeBtn->getRenderer()->setBackgroundColorDown({0,0,0,0});
        startArcadeBtn->getRenderer()->setBorderColorDown({0,0,0,0});
        startArcadeBtn->onPress([this]() { close(); m_onStartArcade(); });
        m_panel->add(startArcadeBtn);

        auto quitBtn = tgui::Button::create("");
        quitBtn->setSize({"440", "145"});
        quitBtn->setPosition({"1285", "893"});
        quitBtn->getRenderer()->setBackgroundColor({0,0,0,0});
        quitBtn->getRenderer()->setBorderColor({0,0,0,0});
        quitBtn->getRenderer()->setBackgroundColorHover({0,0,0,0});
        quitBtn->getRenderer()->setBorderColorHover({0,0,0,0});
        quitBtn->getRenderer()->setBackgroundColorDown({0,0,0,0});
        quitBtn->getRenderer()->setBorderColorDown({0,0,0,0});
        quitBtn->onPress([this]() { close(); m_onQuit(); });
        m_panel->add(quitBtn);
    }

} // namespace tdg::infra
