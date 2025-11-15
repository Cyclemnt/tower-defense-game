#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "tower.hpp"

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

        bool operator<(const Materials& other) const {
            if (au != other.au) return au < other.au;
            if (ag != other.ag) return ag < other.ag;
            return cu < other.cu;
        }
    };

    class Player {
    public:
        explicit Player(const Materials& start);

        bool canAfford(const TowerStats& stats) const;
        void buy(const TowerStats& stats);
        void addMaterials(const Materials& m);
        Materials materials() const noexcept { return m_current; }

    private:
        Materials m_current;
    };

} // namespace tdg::core

#endif // PLAYER_HPP