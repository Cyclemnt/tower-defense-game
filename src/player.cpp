#include "../include/player.hpp"

Player::Player()
    : materials() {}

Player::~Player() {}

bool Player::canAfford(const Tower& tower) {
    for (size_t i = 0; i < 3; i++)
        if (materials.getBalance()[i] < tower.getPrice()[i])
            return false;
    
    return true;
}

void Player::pay(const Tower& tower) {
    materials.spend(tower.getPrice());
}

void Player::addMaterials(std::array<int, 3> loot) {
    materials.add(loot);
}
