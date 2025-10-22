#include "../../include/gui/guiManager.hpp"
#include "../../include/map/openZone.hpp"
#include "../../include/renderer/renderer.hpp"

GuiManager::GuiManager(sf::RenderWindow& window, Game& gm, RenderContext& ctx)
    : gui(window), game(gm), ctx(ctx), hud(ctx, gm), cam(ctx),
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
            else                 { pauseMenu.open();  game.setPaused(true);  }

    bool clickConsumed = false;

    if (auto mouse = event.getIf<sf::Event::MouseButtonPressed>())
        if (!game.isPaused() && mouse->button == sf::Mouse::Button::Left)
            clickConsumed = handleLeftClick(mouse->position.x, mouse->position.y);

    cam.handleZoom(event);

    // Only drag if click not used for tower/menu
    if (!clickConsumed)
        cam.handleDrag(event);

    if (auto mouse = event.getIf<sf::Event::MouseButtonPressed>())
        if (!game.isPaused() && mouse->button == sf::Mouse::Button::Middle)
            cam.resetView();
}

bool GuiManager::handleLeftClick(int mouseX, int mouseY) {
    sf::Vector2i tile = ctx.screenToTile(mouseX, mouseY);
    const Map& map = game.getMap();
    Tile* clicked = map.getTile(tile.x, tile.y);

    if (OpenZone* zone = dynamic_cast<OpenZone*>(clicked)) {
        towerMenu.open(tile, zone->isOccupied());
        game.setPaused(true);
        return true;
    } else return false;
}

void GuiManager::draw(float deltaTime) {
    hud.draw(deltaTime);
    gui.draw();
}
