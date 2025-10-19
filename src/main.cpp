#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "../include/game.hpp"
#include "../include/renderer/renderer.hpp"
#include "../include/gui/guiManager.hpp"
#include "../include/gui/hud.hpp"

int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Tower Defense", sf::State::Fullscreen);
    window.setFramerateLimit(60);

    tgui::Gui gui(window);

    Game game;
    Renderer renderer(window);
    renderer.computeScaling(game);

    HUD hud;
    GuiManager guiManager(gui, game, renderer);

    sf::Clock clock;
    
    while (window.isOpen()) {
        // --- Managing events ---
        while (auto event = window.pollEvent()) {
            // feed our GuiManager
            guiManager.processEvent(*event);
            if (event->is<sf::Event::Closed>()) window.close();
        }

        // --- Update logic ---
        float deltaTime = clock.restart().asSeconds();
        if (!game.isPaused())
            game.update(deltaTime);

        // --- Render ---
        window.clear();
        renderer.render(game);
        hud.render(renderer.getContext(), game, deltaTime);

        gui.draw();
        window.display();
    }

    return 0;
}
