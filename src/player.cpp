#include "../include/player.hpp"

Player::Player()
    : materials(), cores() {}

Player::~Player() {}

void Player::placeTower(Tile* tile, Tower* tower) {
}

void Player::upgradeTower(Tower* tower) {
}

bool Player::canAfford(const Tower& tower) {
    return false;
}

void Player::pay(const Tower& tower) {
    materials.spend(tower.getPrice());
}
