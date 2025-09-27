#include "../include/game.hpp"
#include "../include/towers/mortar.hpp"
#include "../include/creatures/drone.hpp"
#include <iostream>

int main() {
    Game game(5, 5, 24);

    // Add a simple creature
    auto c = std::make_unique<Drone>();
    game.spawnCreature(std::move(c));

    // Add a simple tower
    std::unique_ptr<Tower> t = std::make_unique<Mortar>(2, 0);
    game.placeTower(std::move(t));
    
    // Simulation loop in the console
    game.render();
    for (int i = 0; i < 66 && !game.isGameOver(); i++) {
        game.update(0.2f);
        game.render();
    }

    return 0;
}