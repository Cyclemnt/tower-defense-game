#include "game.hpp"
#include "renderer.hpp"
#include <chrono>

// int main() {
//     const int width = 16;
//     const int height = 16;
//     const int initialCores = 24;
//     const int tileSize = 64;

//     Game game(width, height, initialCores);
//     Renderer renderer(width, height, tileSize);

//     auto lastTime = std::chrono::high_resolution_clock::now();

//     while (renderer.isOpen()) {
//         // Process events (keyboard/mouse/UI)
//         renderer.processEvents(game);

//         // Delta time
//         auto now = std::chrono::high_resolution_clock::now();
//         std::chrono::duration<float> elapsed = now - lastTime;
//         float deltaTime = elapsed.count();
//         lastTime = now;

//         // Game logic
//         game.update(deltaTime);

//         // Rendering
//         renderer.render(game);
//     }

//     return 0;
// }

#include "../include/game.hpp"
#include "../include/renderer.hpp"
#include "../include/towers/gatling.hpp"
#include "../include/creatures/tank.hpp"
#include "../include/creatures/minion.hpp"
#include "../include/creatures/drone.hpp"
#include <iostream>

int main() {
    const int width = 16;
    const int height = 16;
    const int initialCores = 24;
    const int tileSize = 64;

    Game game(width, height, initialCores);
    Renderer renderer(width, height, tileSize);

    // Add a simple creature
    std::unique_ptr<Creature> c = std::make_unique<Tank>();
    game.spawnCreature(std::move(c));
    c = std::make_unique<Minion>();
    game.spawnCreature(std::move(c));
    c = std::make_unique<Drone>();
    game.spawnCreature(std::move(c));

    // Simulation loop in the console
    game.render();
    for (int i = 0; i < 100000 && !game.isGameOver(); i++) {
        game.update(0.002f);
        game.render();
        renderer.render(game);
    }

    return 0;
}