#include "engine/gui/mainMenu.hpp"

namespace tdg::engine {
    
    MainMenu::MainMenu(std::shared_ptr<tgui::Gui> gui, std::shared_ptr<CommandBus> bus)
        : Menu(gui), m_bus(bus)
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

        unsigned int winX = m_gui->getWindow()->getSize().x;
        unsigned int winY = m_gui->getWindow()->getSize().y;

        sf::Vector2f panelSize = sf::Vector2f(m_gui->getWindow()->getSize());
        sf::Vector2f panelPos = centerPanel(panelSize);

        m_panel = tgui::Panel::create({panelSize});
        m_panel->setPosition({panelPos});
        m_panel->getRenderer()->setBackgroundColor({0, 0, 0, 0});
        
        tgui::Picture::Ptr background = tgui::Picture::create("../assets/textures/main_menu.png");
        background->setSize(winX, winY);
        background->setPosition(0, 0);
        m_panel->add(background);

        auto startStoryBtn = tgui::Button::create("");
        startStoryBtn->setSize({440 * winX / 1920.0f, 145 * winY / 1200.0f});
        startStoryBtn->setPosition({195 * winX / 1920.0f, 893 * winY / 1200.0f});
        startStoryBtn->getRenderer()->setBackgroundColor({0,0,0,0});
        startStoryBtn->getRenderer()->setBorderColor({0,0,0,0});
        startStoryBtn->getRenderer()->setBackgroundColorHover({0,0,0,0});
        startStoryBtn->getRenderer()->setBorderColorHover({0,0,0,0});
        startStoryBtn->getRenderer()->setBackgroundColorDown({0,0,0,0});
        startStoryBtn->getRenderer()->setBorderColorDown({0,0,0,0});
        startStoryBtn->onPress([this]() { close(); m_bus->push({Command::Type::StartStory}); });
        m_panel->add(startStoryBtn);

        auto startArcadeBtn = tgui::Button::create("");
        startArcadeBtn->setSize({410 * winX / 1920.0f, 145 * winY / 1200.0f});
        startArcadeBtn->setPosition({755 * winX / 1920.0f, 893 * winY / 1200.0f});
        startArcadeBtn->getRenderer()->setBackgroundColor({0,0,0,0});
        startArcadeBtn->getRenderer()->setBorderColor({0,0,0,0});
        startArcadeBtn->getRenderer()->setBackgroundColorHover({0,0,0,0});
        startArcadeBtn->getRenderer()->setBorderColorDownHover({0,0,0,0});
        startArcadeBtn->getRenderer()->setBorderColorHover({0,0,0,0});
        startArcadeBtn->getRenderer()->setBackgroundColorDown({0,0,0,0});
        startArcadeBtn->getRenderer()->setBorderColorDown({0,0,0,0});
        startArcadeBtn->onPress([this]() { close(); m_bus->push({Command::Type::StartArcade}); });
        m_panel->add(startArcadeBtn);

        auto quitBtn = tgui::Button::create("");
        quitBtn->setSize({440 * winX / 1920.0f, 145 * winY / 1200.0f});
        quitBtn->setPosition({1285 * winX / 1920.0f, 893 * winY / 1200.0f});
        quitBtn->getRenderer()->setBackgroundColor({0,0,0,0});
        quitBtn->getRenderer()->setBorderColor({0,0,0,0});
        quitBtn->getRenderer()->setBackgroundColorHover({0,0,0,0});
        quitBtn->getRenderer()->setBorderColorHover({0,0,0,0});
        quitBtn->getRenderer()->setBackgroundColorDown({0,0,0,0});
        quitBtn->getRenderer()->setBorderColorDown({0,0,0,0});
        quitBtn->onPress([this]() { close(); m_bus->push({Command::Type::Quit}); });
        m_panel->add(quitBtn);
    }

} // namespace tdg::engine
