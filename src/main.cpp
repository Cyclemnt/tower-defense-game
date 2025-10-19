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

    Game game;
    Renderer renderer(window, game);
    GuiManager guiManager(window, game, renderer.getContext());

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
        renderer.render();
        guiManager.draw(deltaTime);

        window.display();
    }

    return 0;
}
