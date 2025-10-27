#include "../include/player.hpp"
#include "../include/towers/tower.hpp"

Player::Player(Materials balance_)
    : balance(balance_) {}

Player::~Player() {}

bool Player::canAfford(const Tower& tower) {
    return balance.canAfford(tower.getCost());
}

void Player::buy(const Tower& tower) {
    balance.spend(tower.getCost());
}

void Player::addMaterials(const Materials::Quantities& loot) {
    balance.add(loot);
}
