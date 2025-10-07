#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "../include/game.hpp"
#include "../include/renderer.hpp"
#include "../include/creatures/tank.hpp"
#include <memory>

int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Tower Defense");
    window.setFramerateLimit(60);

    tgui::Gui gui(window);
    Game game(16, 10, 24);
    Renderer renderer(window, gui);

    std::unique_ptr<Creature> c = std::make_unique<Tank>();
    game.spawnCreature(std::move(c));

    sf::Clock clock;
    bool paused = false;
    
    while (window.isOpen()) {
        // --- Gestion des événements ---
        while (auto event = window.pollEvent()) {
            gui.handleEvent(*event);

            // Fermeture de la fenêtre
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Clic souris
            if (!paused) {
                if (auto mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                    renderer.handleMouseClick(mouse->position.x, mouse->position.y, game);
                }
            }

            // Touche ESC → pause
            if (auto key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Escape) {
                    paused = !paused;
                    renderer.togglePauseMenu(paused, game);
                }
            }
        }

        // --- Mise à jour logique ---
        float deltaTime = clock.restart().asSeconds();
        if (!paused)
            game.update(deltaTime);

        // --- Rendu ---
        window.clear();
        renderer.render(game);
        gui.draw();
        window.display();
    }

    return 0;
}
