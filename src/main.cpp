#include "game.hpp"
#include "renderer.hpp"
#include <chrono>

int main() {
    const int width = 10;
    const int height = 10;
    const int initialCores = 24;
    const int tileSize = 64;

    Game game(width, height, initialCores);
    Renderer renderer(width, height, tileSize);

    auto lastTime = std::chrono::high_resolution_clock::now();

    while (renderer.isOpen()) {
        // Gestion des événements (clavier/souris/UI)
        renderer.processEvents(game);

        // Delta time
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsed = now - lastTime;
        float deltaTime = elapsed.count();
        lastTime = now;

        // Logique du jeu
        game.update(deltaTime);

        // Affichage
        renderer.render(game);
    }

    return 0;
}



// #include "../include/game.hpp"
// #include "../include/towers/mortar.hpp"
// #include "../include/creatures/drone.hpp"
// #include <iostream>

// int main() {
//     Game game(5, 5, 24);

//     // Add a simple creature
//     auto c = std::make_unique<Drone>();
//     game.spawnCreature(std::move(c));

//     // Add a simple tower
//     std::unique_ptr<Tower> t = std::make_unique<Mortar>(2, 0);
//     game.placeTower(std::move(t));
    
//     // Simulation loop in the console
//     game.render();
//     for (int i = 0; i < 66 && !game.isGameOver(); i++) {
//         game.update(0.2f);
//         game.render();
//     }

//     return 0;
// }