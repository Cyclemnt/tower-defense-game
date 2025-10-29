#include "../../include/gui/pauseMenu.hpp"

PauseMenu::PauseMenu(tgui::Gui& gui_, Game& game_, const RenderContext& ctx_) noexcept
    : Menu(gui_, game_, ctx_)
{
    sf::Vector2f panelSize = {300.0f, 200.0f};
    sf::Vector2f panelPos = centerPanel(panelSize);

    panel = tgui::Panel::create({panelSize});
    panel->setPosition({panelPos});
    panel->getRenderer()->setBackgroundColor({0, 0, 0, 180});

    auto label = tgui::Label::create("Game Paused");
    label->setTextSize(18);
    label->getRenderer()->setTextColor(tgui::Color::White);
    label->setPosition({10, 10});
    panel->add(label);

    auto resumeBtn = tgui::Button::create("Resume");
    resumeBtn->setSize({"280", "40"});
    resumeBtn->setPosition({"10", "150"});
    resumeBtn->onPress([this]() { close(); game.setPaused(false); });
    panel->add(resumeBtn);
}

void PauseMenu::open() {
    if (on) return;
    gui.add(panel);
    on = true;
}
