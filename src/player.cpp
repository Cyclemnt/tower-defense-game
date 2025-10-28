#include "../include/player.hpp"
#include "../include/towers/tower.hpp"

Player::Player(Materials initialBalance) noexcept
    : balance(std::move(initialBalance)) {}

bool Player::canAfford(const Tower& tower) const noexcept {
    return balance.canAfford(tower.getCost());
}

void Player::buy(const Tower& tower) noexcept {
    balance.spend(tower.getCost());
}

void Player::addMaterials(const Materials::Quantities& loot) noexcept {
    balance.add(loot);
}
