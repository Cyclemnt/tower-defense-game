#include "engine/game.hpp"

int main() {
    tdg::engine::Game game(1u);

    for (int i = 0; i < 2000; i++) {
        game.update(0.4);
    }
    
    return 0;
}
