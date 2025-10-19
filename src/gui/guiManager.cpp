#include "../../include/gui/guiManager.hpp"
#include "../../include/map/openZone.hpp"
#include "../../include/renderer/renderer.hpp"

GuiManager::GuiManager(sf::RenderWindow& window, Game& gm, RenderContext& ctx)
    : gui(window), game(gm), ctx(ctx), hud(ctx, gm),
      pauseMenu(gui, gm, ctx), towerMenu(gui, gm, ctx)
{
    try {
        gui.setFont("../assets/gui/arial.ttf");
    } catch (...) {}
}

void GuiManager::processEvent(const sf::Event& event) {
    gui.handleEvent(event);

    if (auto key = event.getIf<sf::Event::KeyPressed>())
        if (!towerMenu.isOn() && key->code == sf::Keyboard::Key::Escape)
            if (game.isPaused()) { pauseMenu.close(); game.setPaused(false); }
            else                 { pauseMenu.open(); game.setPaused(true);  }

    if (auto mouse = event.getIf<sf::Event::MouseButtonPressed>())
        if (!game.isPaused() && mouse->button == sf::Mouse::Button::Left)
            handleLeftClick(mouse->position.x, mouse->position.y);
}

void GuiManager::handleLeftClick(int mouseX, int mouseY) {
    sf::Vector2i tile = ctx.screenToTile(mouseX, mouseY);
    const Map& map = game.getMap();
    Tile* clicked = map.getTile(tile.x, tile.y);
    if (auto* zone = dynamic_cast<OpenZone*>(clicked)) {
        if (!zone->isOccupied()) {
            game.setPaused(true);
            towerMenu.open(tile);
        }
    }
}

void GuiManager::draw(float deltaTime) {
    hud.draw(deltaTime);
    gui.draw();
}
