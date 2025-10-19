#include <iostream>
#include "../../include/gui/guiManager.hpp"
#include "../../include/game.hpp"
#include "../../include/renderer/renderer.hpp"
#include "../../include/towers/gatling.hpp"
#include "../../include/towers/laser.hpp"
#include "../../include/towers/mortar.hpp"
#include "../../include/map/openZone.hpp"

GuiManager::GuiManager(tgui::Gui& g, Game& gm, Renderer& r)
    : gui(g), game(gm), renderer(r) {
    // Optionally set a default font if you want
    try {
        // if you have a theme file, load it here; otherwise TGUI uses default.
        gui.setFont("../assets/gui/arial.ttf");
    } catch (...) {
        // ignore - not fatal
    }
}

// processEvent : call this from main event loop, before calling gui.handleEvent(event) or after
void GuiManager::processEvent(const sf::Event& event) {
    // Pass to TGUI first
    gui.handleEvent(event);

    // Handle Escape to toggle pause menu
    if (auto key = event.getIf<sf::Event::KeyPressed>())
        if (key->code == sf::Keyboard::Key::Escape)
            togglePause();

    // Left mouse click -> open tower menu
    if (auto mouse = event.getIf<sf::Event::MouseButtonPressed>())
        handleLeftClick(mouse->position.x, mouse->position.y);
}

void GuiManager::handleLeftClick(int mouseX, int mouseY) {
    // Convert window coords -> tile coords using renderer
    sf::Vector2i tile = renderer.screenToTile(mouseX, mouseY);

    const Map& map = game.getMap();
    Tile* clicked = map.getTile(tile.x, tile.y);
    if (!clicked) return;

    // Only open tower menu on OpenZone (and if not occupied)
    if (dynamic_cast<OpenZone*>(clicked)) {
        openTowerMenuAtTile(tile);
    }
}

void GuiManager::togglePause() {
    paused = !paused;
    if (paused) openPauseMenu();
    else closePauseMenu();
    // Let the game know
    game.setPaused(paused);
}

void GuiManager::openPauseMenu() {
    gui.removeAllWidgets(); // simple approach
    pausePanel = tgui::Panel::create({"300", "200"});
    pausePanel->setPosition({"center", "center"});
    pausePanel->getRenderer()->setBackgroundColor({10,10,10,220});

    auto label = tgui::Label::create("Game Paused");
    label->setPosition({"center", "10"});
    pausePanel->add(label);

    auto resumeBtn = tgui::Button::create("Resume");
    resumeBtn->setSize({"200", "40"});
    resumeBtn->setPosition({"center", "80"});
    resumeBtn->onPress([this]() {
        togglePause();
    });
    pausePanel->add(resumeBtn);

    gui.add(pausePanel);
}

void GuiManager::closePauseMenu() {
    if (pausePanel) {
        gui.remove(pausePanel);
        pausePanel.reset();
    }
    gui.removeAllWidgets(); // optionally remove all (may remove tower menu also)
}

void GuiManager::openTowerMenuAtTile(const sf::Vector2i& tilePos) {
    // Pause the game while menu is open
    if (!paused) {
        paused = true;
        try { game.setPaused(true); } catch (...) {}
    } else return; // Do not open menu if game is paused

    // Remove any existing tower menu first
    if (towerMenu) gui.remove(towerMenu); // Unnecessary if menu can't be opened when game is paused but we never know
 
    sf::Vector2u win = renderer.getContext().window.getSize();
    float panelW = 220.f;
    float panelH = 250.f;
    float panelX = (win.x - panelW) * 0.5f;
    float panelY = (win.y - panelH) * 0.5f;

    towerMenu = tgui::Panel::create({panelW, panelH});
    towerMenu->setPosition({panelX, panelY});
    towerMenu->getRenderer()->setBackgroundColor({40, 40, 40, 230});

    auto title = tgui::Label::create("Build a tower");
    title->setTextSize(18);
    title->getRenderer()->setTextColor(tgui::Color::White);
    title->setPosition({10, 10});

    towerMenu->add(title);

    auto addBtn = [&](const std::string& label, auto factory, const std::string& costText, float y) {
        auto btn = tgui::Button::create(label + "\n" + costText);
        btn->setSize({"200", "38"});
        btn->setPosition(10, y);
        btn->onPress([this, factory, tilePos]() {
            // create tower and attempt to place
            auto tower = factory(tilePos.x, tilePos.y);
            PlaceTowerResult res = game.placeTower(std::move(tower));
            switch (res) {
                case PlaceTowerResult::NotBuildable: showError("Cannot build here."); break;
                case PlaceTowerResult::NotAffordable: showError("Not enough materials."); break;
                case PlaceTowerResult::Occupied: showError("Occupied."); break;
                case PlaceTowerResult::Success:
                    // optional: visual feedback
                    break;
            }
            closeTowerMenu();
            // Unpause
            paused = false;
            try { game.setPaused(false); } catch(...) {}
        });
        towerMenu->add(btn);
    };

    addBtn("Gatling", [](int x,int y){ return std::make_unique<Gatling>(x,y); }, "50 Cu", 58.0f);
    addBtn("Laser",   [](int x,int y){ return std::make_unique<Laser>(x,y); }, "10 Ag, 100 Cu", 106.0f);
    addBtn("Mortar",  [](int x,int y){ return std::make_unique<Mortar>(x,y); }, "75 Cu", 154.0f);

    // Cancel button
    auto cancel = tgui::Button::create("Cancel");
    cancel->setSize({"200", "34"});
    cancel->setPosition(10, 202);
    cancel->onPress([this]() {
        closeTowerMenu();
        paused = false;
        game.setPaused(false);
    });
    towerMenu->add(cancel);

    gui.add(towerMenu);
}

void GuiManager::closeTowerMenu() {
    if (towerMenu) {
        gui.remove(towerMenu);
        towerMenu.reset();
    }
}

void GuiManager::showError(const std::string& message) {
    if (errorPanel) gui.remove(errorPanel);
    errorPanel = tgui::Panel::create({"50%", "8%"});
    errorPanel->setPosition({"25%", "5%"});
    errorPanel->getRenderer()->setBackgroundColor({200,50,50,230});

    auto label = tgui::Label::create(message);
    label->setPosition(10, 10);
    label->getRenderer()->setTextColor(tgui::Color::White);
    label->setTextSize(16);
    errorPanel->add(label);

    gui.add(errorPanel);

    scheduleRemoveWidget(errorPanel, 2000);
}

void GuiManager::scheduleRemoveWidget(tgui::Widget::Ptr widget, unsigned int ms) {
    if (!widget) return;
    std::shared_ptr<tgui::Timer> timer = tgui::Timer::create([widget, this]() {
        try { gui.remove(widget); } catch(...) {}
    }, std::chrono::milliseconds(ms));
}

