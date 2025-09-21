#include "../include/game.hpp"

#include <iostream>

int main() {
    Game game(5, 5, 24);

    // Ajouter une créature simple
    auto c = std::make_unique<Creature>(30, 5, 1.0f);
    game.spawnCreature(std::move(c));

    // Ajouter une tour simple
    auto t = std::make_unique<Tower>(2, 0, 10, 0, 0, 5, 3.0f, 1.0f, false);
    game.placeTower(std::move(t));

    // Boucle de simulation console
        game.render();
    for (int i = 0; i < 10 && !game.isGameOver(); i++) {
        game.update();
        game.render();
    }

    return 0;
}