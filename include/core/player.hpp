#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "core/towers/tower.hpp"

namespace tdg::core {

    struct Materials {
        unsigned int au, ag, cu;

        Materials(unsigned int au = 0, unsigned int ag = 0, unsigned int cu = 0) : au(au), ag(ag), cu(cu) {}

        Materials operator/(unsigned int den) const {
            return {au / den, ag / den, cu / den};
        }

        Materials& operator+=(const Materials& other) {
            au += other.au;
            ag += other.ag;
            cu += other.cu;
            return *this;
        }

        Materials& operator-=(const Materials& other) {
            au -= other.au;
            ag -= other.ag;
            cu -= other.cu;
            return *this;
        }
    };

    class Player {
    public:
        explicit Player(const Materials& startBalance);

        bool canAfford(const Materials& cost) const;
        void buy(const Materials& cost);
        void addMaterials(const Materials& m);
        Materials materials() const noexcept { return m_balance; }

    private:
        Materials m_balance;
    };

} // namespace tdg::core

#endif // PLAYER_HPP