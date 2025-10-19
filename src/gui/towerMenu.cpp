#include "../../include/gui/towerMenu.hpp"
#include "../../include/towers/gatling.hpp"
#include "../../include/towers/laser.hpp"
#include "../../include/towers/mortar.hpp"
#include "../../include/map/openZone.hpp"

TowerMenu::TowerMenu(tgui::Gui& gui, Game& gm, RenderContext& ctx)
    : Menu(gui, gm, ctx) {}

void TowerMenu::open(sf::Vector2i pos, bool occ) {
    if (on) return;
    tilePos = pos;
    occupied = occ;

    buildBasePanel();
    if (occupied) buildSellPanel();
    else buildBuildPanel();
    addCancelButton();

    gui.add(panel);
    on = true;
}

void TowerMenu::buildBasePanel() {
    float panelW = 220.f, panelH = 250.f;
    auto [panelX, panelY] = centerPanel(panelW, panelH);
    panel = tgui::Panel::create({panelW, panelH});
    panel->setPosition({panelX, panelY});
    panel->getRenderer()->setBackgroundColor({40, 40, 40, 230});
}

void TowerMenu::buildBuildPanel() {
    auto title = tgui::Label::create("Build a tower");
    title->setTextSize(18);
    title->getRenderer()->setTextColor(tgui::Color::White);
    title->setPosition({10, 10});
    panel->add(title);

    addTowerButton("Gatling", [](int x, int y){ return std::make_unique<Gatling>(x, y); }, "50 Cu", 58);
    addTowerButton("Laser",   [](int x, int y){ return std::make_unique<Laser>(x, y); }, "10 Ag, 100 Cu", 106);
    addTowerButton("Mortar",  [](int x, int y){ return std::make_unique<Mortar>(x, y); }, "75 Cu", 154);
}

void TowerMenu::buildSellPanel() {
    auto title = tgui::Label::create("Sell this tower?");
    title->setTextSize(18);
    title->getRenderer()->setTextColor(tgui::Color::White);
    title->setPosition({10, 10});
    panel->add(title);

    auto sellBtn = tgui::Button::create("Sell for 50%");
    sellBtn->setSize({"200", "38"});
    sellBtn->setPosition({10, 58});
    sellBtn->onPress([this]() {
        game.sellTowerAt(tilePos.x, tilePos.y);
        close();
        game.setPaused(false);
    });
    panel->add(sellBtn);
}

void TowerMenu::addTowerButton(const std::string& name,
                               std::function<std::unique_ptr<Tower>(int, int)> factory,
                               const std::string& cost,
                               float y) {
    auto btn = tgui::Button::create(name + "\n" + cost);
    btn->setSize({"200", "38"});
    btn->setPosition({10, y});
    btn->onPress([this, factory]() {
        auto tower = factory(tilePos.x, tilePos.y);
        auto result = game.placeTower(std::move(tower));
        switch (result) {
            case PlaceTowerResult::NotBuildable: showError("Cannot build here."); break;
            case PlaceTowerResult::NotAffordable: showError("Not enough materials."); break;
            case PlaceTowerResult::Occupied: showError("Tile is occupied."); break;
            case PlaceTowerResult::Success: break;
        }
        close();
        game.setPaused(false);
    });
    panel->add(btn);
}

void TowerMenu::addCancelButton() {
    auto cancel = tgui::Button::create("Cancel");
    cancel->setSize({"200", "34"});
    cancel->setPosition({10, 202});
    cancel->onPress([this]() { close(); game.setPaused(false); });
    panel->add(cancel);
}

void TowerMenu::showError(const std::string& message) { // This shouldn't be here but isn't useful elsewhere for now
    auto errorPanel = tgui::Panel::create({"50%", "8%"});
    errorPanel->setPosition({"25%", "5%"});
    errorPanel->getRenderer()->setBackgroundColor({200, 50, 50, 230});

    auto label = tgui::Label::create(message);
    label->setPosition(10, 10);
    label->getRenderer()->setTextColor(tgui::Color::White);
    label->setTextSize(16);
    errorPanel->add(label);

    gui.add(errorPanel);
    scheduleRemoveWidget(errorPanel, 2000);
}

void TowerMenu::scheduleRemoveWidget(tgui::Widget::Ptr widget, unsigned int ms) {
    if (!widget) return;
    auto timer = tgui::Timer::create([this, widget]() {
        gui.remove(widget);
    }, std::chrono::milliseconds(ms));
}
