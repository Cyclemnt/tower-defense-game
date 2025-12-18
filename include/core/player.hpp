#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "core/materials.hpp"

namespace tdg::core {

    class Player {
    public:
        explicit Player(const Materials& startBalance);

        bool canAfford(const Materials& cost) const;
        void buy(const Materials& cost);
        void addMaterials(const Materials& m);
        const Materials& materials() const noexcept { return m_balance; }

    private:
        Materials m_balance;
    };

} // namespace tdg::core

#endif // PLAYER_HPP