#include "../include/game.hpp"
#include "../include/towers/laser.hpp"
#include "../include/creatures/minion.hpp"
#include <iostream>

int main() {
    Game game(5, 5, 24);

    // Ajouter une créature simple
    auto c = std::make_unique<Minion>();
    game.spawnCreature(std::move(c));

    // Ajouter une tour simple
    std::unique_ptr<Tower> t = std::make_unique<Laser>(2, 0);
    game.placeTower(std::move(t));

    // Boucle de simulation console
    game.render();
    for (int i = 0; i < 10 && !game.isGameOver(); i++) {
        game.update();
        game.render();
    }

    return 0;
}