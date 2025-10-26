#include "../include/player.hpp"
#include "../include/towers/tower.hpp"

Player::Player()
    : materials() {}

Player::~Player() {}

const Materials& Player::getMaterials() const { return materials; }
Materials& Player::getMaterials() { return materials; }

bool Player::canAfford(const Tower& tower) {
    for (size_t i = 0; i < 3; ++i)
        if (materials.getBalance()[i] < tower.getCost()[i])
            return false;
    
    return true;
}

void Player::pay(const Tower& tower) {
    materials.spend(tower.getCost());
}

void Player::addMaterials(std::array<unsigned int, 3> loot) {
    materials.add(loot);
}
