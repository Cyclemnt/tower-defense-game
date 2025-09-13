#include "../include/player.hpp"

Player::Player()
    : materials(), cores() {}

Player::~Player() {}

void Player::placeTower(Tile* tile, Tower* tower) {
}

void Player::upgradeTower(Tower* tower) {
}

bool Player::canAfford(Tower* tower) const {
    return false;
}
