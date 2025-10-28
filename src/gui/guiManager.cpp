#include "../../include/gui/guiManager.hpp"
#include "../../include/tiles/openZone.hpp"
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
        else towerMenu.close();

    bool clickConsumed = false;

    if (auto mouse = event.getIf<sf::Event::MouseButtonPressed>())
        if (!game.isPaused() && mouse->button == sf::Mouse::Button::Left)
            clickConsumed = handleLeftClick(mouse->position); // TODO: when click outside towerMenu, close it.

    if (!game.isPaused())
        cam.handleZoom(event);

    // Only drag if click not used for tower/menu
    if (!clickConsumed && !game.isPaused())
        cam.handleDrag(event);

    if (auto mouse = event.getIf<sf::Event::MouseButtonPressed>())
        if (!game.isPaused() && mouse->button == sf::Mouse::Button::Middle)
            cam.resetView();
}

bool GuiManager::handleLeftClick(sf::Vector2i mousePos) {
    sf::Vector2i tilePos = ctx.screenToTile(mousePos);
    const Map& map = game.getMap();
    Tile* clicked = map.getTile(tilePos);

    if (OpenZone* zone = dynamic_cast<OpenZone*>(clicked)) {
        towerMenu.open(tilePos, zone->isOccupied());
        return true;
    } else return false;
}

void GuiManager::draw(float deltaTime) {
    hud.draw(deltaTime);
    gui.draw();
}
