#include "../include/game.hpp"
#include "../include/towers/gatling.hpp"
#include "../include/creatures/drone.hpp"
#include <iostream>

int main() {
    Game game(5, 5, 24);

    // Add a simple creature
    auto c = std::make_unique<Drone>();
    game.spawnCreature(std::move(c));

    // Add a simple tower
    std::unique_ptr<Tower> t = std::make_unique<Gatling>(2, 0);
    game.placeTower(std::move(t));
    std::cout << "Here the creature is autonomous\nit goes to the core storage then to the exit.\n";
    // Simulation loop in the console
    game.render();
    for (int i = 0; i < 66 && !game.isGameOver(); i++) {
        game.update(0.1f);
        game.render();
    }

    return 0;
}