#include "../include/game.hpp"
#include "game.hpp"

Game::Game()
    : map(2, 2), towers({}), creatures({}), player(), elapsedTime(0) {}

Game::~Game() {}

void Game::run() {
    map.printMap();
}

void Game::update() {
}

void Game::render() {
}

void Game::spawnWave() {
}
