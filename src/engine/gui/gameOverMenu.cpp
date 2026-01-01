#include "engine/gui/gameOverMenu.hpp"

namespace tdg::engine {
    
    GameOverMenu::GameOverMenu(std::shared_ptr<tgui::Gui> gui, std::shared_ptr<CommandBus> bus)
        : Menu(gui), m_bus(bus)
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
        restartLevelBtn->onPress([this]() { close(); m_bus->push({Command::Type::RestartLevel}); });
        m_panel->add(restartLevelBtn);

        auto mainMenuBtn = tgui::Button::create("Main Menu");
        mainMenuBtn->setSize({"280", "40"});
        mainMenuBtn->setPosition({"10", "150"});
        mainMenuBtn->onPress([this]() { close(); m_bus->push({Command::Type::MainMenu}); });
        m_panel->add(mainMenuBtn);

        auto quitBtn = tgui::Button::create("Quit");
        quitBtn->setSize({"280", "40"});
        quitBtn->setPosition({"10", "200"});
        quitBtn->onPress([this]() { close(); m_bus->push({Command::Type::Quit}); });
        m_panel->add(quitBtn);

    }

} // namespace tdg::engine
