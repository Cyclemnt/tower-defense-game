#include "../../include/gui/pauseMenu.hpp"

PauseMenu::PauseMenu(tgui::Gui& gui, Game& gm, RenderContext& ctx)
    : Menu(gui, gm, ctx) {}

void PauseMenu::open() {
    if (on) return;

    float panelW = 300.f, panelH = 200.f;
    auto [panelX, panelY] = centerPanel(panelW, panelH);

    panel = tgui::Panel::create({panelW, panelH});
    panel->setPosition({panelX, panelY});
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

    gui.add(panel);
    on = true;
}
