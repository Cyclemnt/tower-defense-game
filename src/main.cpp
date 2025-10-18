#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "../include/game.hpp"
#include "../include/renderer/renderer.hpp"
#include "../include/visual-effects/visualEffect.hpp"
#include "../include/towers/tower.hpp"

int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Tower Defense", sf::State::Fullscreen);

    window.setFramerateLimit(60);

    tgui::Gui gui(window);
    Game game;
    Renderer renderer(window, gui);
    renderer.computeScaling(game);

    sf::Clock clock;
    bool paused = false;
    
    while (window.isOpen()) {
        // --- Managing events ---
        while (auto event = window.pollEvent()) {
            gui.handleEvent(*event);

            // Closing window
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Mouse clic
            if (!paused) {
                if (auto mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                    renderer.handleMouseClick(mouse->position.x, mouse->position.y, game);
                }
            }

            // ESC key
            if (auto key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Escape) {
                    paused = !paused;
                    renderer.togglePauseMenu(paused, game);
                }
            }
        }

        // --- Update logic ---
        float deltaTime = clock.restart().asSeconds();
        if (!paused)
            game.update(deltaTime * 10);

        // --- Render ---
        window.clear();
        renderer.render(game);

        gui.draw();
        window.display();
    }

    return 0;
}
