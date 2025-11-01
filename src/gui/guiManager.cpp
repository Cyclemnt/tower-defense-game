#include <iostream>
#include "../../include/gui/guiManager.hpp"
#include "../../include/tiles/openZone.hpp"
#include "../../include/renderer/renderer.hpp"

GuiManager::GuiManager(sf::RenderWindow& window, Game& game_, RenderContext& ctx_)
    : gui(window), game(game_), ctx(ctx_), hud(ctx_, game_), camera(ctx_),
      pauseMenu(gui, game_, ctx_), towerPanel(ctx_, game_)
{
    try {
        gui.setFont("../assets/gui/Lexend-Black.ttf");
    } catch (...) {
        std::cerr << "[GuiManager] Warning: failed to load GUI font.\n";
    }
}

void GuiManager::processEvent(const sf::Event& event) {
    gui.handleEvent(event);

    // Manage keys
    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
        if (key->code == sf::Keyboard::Key::Escape) {
            if (game.isPaused()) { pauseMenu.close(); game.setPaused(false); }
            else                 { pauseMenu.open();  game.setPaused(true);  }
        }
    }

    if (game.isOver()) return;

    // Manage clics
    if (!game.isPaused()) {
        if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mouse->button == sf::Mouse::Button::Left) {
                // Click on panel first
                if (towerPanel.handleClick(mouse->position))
                    return; // Clic consumed

                // Then, check for tile click
                if (!game.isPaused()) {
                    sf::Vector2i tilePos = ctx.screenToTile(mouse->position);
                    towerPanel.handleTileClick(tilePos);
                }
            }
            if (mouse->button == sf::Mouse::Button::Right)
                game.accelerate();
        } else if (const auto* mouse = event.getIf<sf::Event::MouseButtonReleased>()) {
            if (mouse->button == sf::Mouse::Button::Right)
                game.resetSpeed();
        }
    }

    // Manage view
    if (!game.isPaused()) {
        camera.handleZoom(event);
        camera.handleDrag(event);

        if (const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mouse->button == sf::Mouse::Button::Middle)
                camera.resetView();
        }
    }
}

void GuiManager::draw(float deltaTime) {
    towerPanel.draw();
    hud.draw(deltaTime);
    gui.draw();
}
