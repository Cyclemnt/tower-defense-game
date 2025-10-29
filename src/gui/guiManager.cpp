#include <iostream>
#include "../../include/gui/guiManager.hpp"
#include "../../include/tiles/openZone.hpp"
#include "../../include/renderer/renderer.hpp"

GuiManager::GuiManager(sf::RenderWindow& window, Game& game_, RenderContext& ctx_)
    : gui(window), game(game_), ctx(ctx_), hud(ctx_, game_), camera(ctx_),
      pauseMenu(gui, game_, ctx_), towerMenu(gui, game_, ctx_)
{
    try {
        gui.setFont("../assets/gui/arial.ttf");
    } catch (...) {
        std::cerr << "[GuiManager] Warning: failed to load GUI font.\n";
    }
}

void GuiManager::processEvent(const sf::Event& event) {
    gui.handleEvent(event);

    // Toggle pause menu with ESC
    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
        if (!towerMenu.isOn() && key->code == sf::Keyboard::Key::Escape) {
            if (game.isPaused()) { pauseMenu.close(); game.setPaused(false); }
            else                 { pauseMenu.open();  game.setPaused(true);  }
        } else {
            towerMenu.close();
        }
    }

    bool clickConsumed = false;

    if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (!game.isPaused() && mouse->button == sf::Mouse::Button::Left)
            clickConsumed = handleLeftClick(mouse->position);
    }

    if (!game.isPaused()) {
        camera.handleZoom(event);
        if (!clickConsumed)
            camera.handleDrag(event);
    }

    if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (!game.isPaused() && mouse->button == sf::Mouse::Button::Middle)
            camera.resetView();
    }
}

bool GuiManager::handleLeftClick(const sf::Vector2i& mousePos) {
    const sf::Vector2i tilePos = ctx.screenToTile(mousePos);
    const Map& map = game.getMap();

    if (OpenZone* zone = dynamic_cast<OpenZone*>(map.getTile(tilePos))) {
        towerMenu.open(tilePos, zone->isOccupied());
        return true;
    }
    return false;
}

void GuiManager::draw(float deltaTime) {
    hud.draw(deltaTime);
    gui.draw();
}
