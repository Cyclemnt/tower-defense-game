#include "../../include/gui/towerMenu.hpp"
#include "../../include/towers/gatling.hpp"
#include "../../include/towers/laser.hpp"
#include "../../include/towers/mortar.hpp"
#include "../../include/tiles/openZone.hpp"

TowerMenu::TowerMenu(tgui::Gui& gui, Game& game, const RenderContext& ctx) noexcept
    : Menu(gui, game, ctx) {}

void TowerMenu::open(const sf::Vector2i& tilePos_, bool occupied_) {
    if (on) return;
    tilePos = tilePos_;
    occupied = occupied_;

    buildBasePanel();
    if (occupied) buildSellPanel();
    else buildBuildPanel();
    addCancelButton();

    gui.add(panel);
    on = true;
}

void TowerMenu::buildBasePanel() {
    sf::Vector2f panelSize = {220.0f, 250.0f};
    sf::Vector2f panelPos = centerPanel(panelSize);
    panel = tgui::Panel::create({panelSize});
    panel->setPosition({panelPos});
    panel->getRenderer()->setBackgroundColor({40, 40, 40, 230});
}

void TowerMenu::buildBuildPanel() {
    auto title = tgui::Label::create("Build a tower");
    title->setTextSize(18);
    title->getRenderer()->setTextColor(tgui::Color::White);
    title->setPosition({10, 10});
    panel->add(title);

    addTowerButton("Gatling", [](sf::Vector2i pos){ return std::make_unique<Gatling>(pos); }, "50 Cu", 58);
    addTowerButton("Laser",   [](sf::Vector2i pos){ return std::make_unique<Laser>(pos); }, "10 Ag, 100 Cu", 106);
    addTowerButton("Mortar",  [](sf::Vector2i pos){ return std::make_unique<Mortar>(pos); }, "75 Cu", 154);
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
    sellBtn->onPress([this]() { game.sellTowerAt(tilePos); close(); });
    panel->add(sellBtn);
}

void TowerMenu::addTowerButton(const std::string& name, std::function<std::unique_ptr<Tower>(sf::Vector2i)> factory,
                               const std::string& cost, float y) {
    tgui::Button::Ptr btn = tgui::Button::create(name + "\n" + cost);
    btn->setSize({"200", "38"});
    btn->setPosition({10, y});
    btn->onPress([this, factory]() {
        std::unique_ptr<Tower> tower = factory(tilePos);
        PlaceTowerResult result = game.placeTower(std::move(tower));
        switch (result) {
            case PlaceTowerResult::NotBuildable: showError("Cannot build here."); break;
            case PlaceTowerResult::NotAffordable: showError("Not enough materials."); break;
            case PlaceTowerResult::Occupied: showError("Tile is occupied."); break;
            case PlaceTowerResult::Success: break;
        }
        close();
    });
    panel->add(btn);
}

void TowerMenu::addCancelButton() {
    auto cancel = tgui::Button::create("Cancel");
    cancel->setSize({"200", "34"});
    cancel->setPosition({10, 202});
    cancel->onPress([this]() { close(); });
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
    std::shared_ptr<tgui::Timer> timer = tgui::Timer::create([this, widget]() { gui.remove(widget); }, std::chrono::milliseconds(ms));
}
