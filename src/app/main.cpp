#include "engine/gameManager.hpp"

int main() {
    tdg::engine::GameManager gameManager;
    gameManager.setState(tdg::engine::GameManager::State::Story);
    
    return 0;
}
