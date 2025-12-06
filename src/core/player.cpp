#include <stdexcept>
#include "core/player.hpp"

namespace tdg::core {

    Player::Player(const Materials& startBalance)
        : m_balance(startBalance) {}

    bool Player::canAfford(const Materials& cost) const {
        if (m_balance.au >= cost.au && m_balance.ag >= cost.ag && m_balance.cu >= cost.cu)
            return true;
        else return false;
    }

    void Player::buy(const Materials& cost) {
        if (!canAfford(cost)) throw std::runtime_error("Attempting to spend more materials than available.");
        m_balance -= cost;
    }
    
    void Player::addMaterials(const Materials& m) {
        m_balance += m;
    }

} // namespace tdg::core