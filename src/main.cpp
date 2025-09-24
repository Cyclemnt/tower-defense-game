#include "../include/game.hpp"
#include "../include/towers/gatling.hpp"
#include "../include/creatures/minion.hpp"
#include <iostream>

int main() {
    Game game(5, 5, 24);

    // Add a simple creature
    auto c = std::make_unique<Minion>();
    game.spawnCreature(std::move(c));

    // Add a simple tower
    std::unique_ptr<Tower> t = std::make_unique<Gatling>(2, 0); // We shouldn't be able to create a base Tower object
    //game.placeTower(std::move(t));
    std::cout << "Here the creature is autonomous\nit goes to the core storage then to the exit.\n";
    // Simulation loop in the console
    game.render();
    for (int i = 0; i < 66 && !game.isGameOver(); i++) {
        game.update(0.2f);
        game.render();
    }

    return 0;
}