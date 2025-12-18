#ifndef MATERIALS_HPP
#define MATERIALS_HPP

namespace tdg::core {
    
        struct Materials {
        unsigned int au{0u}, ag{0u}, cu{0u};

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

} // namespace tdg::core

#endif // MATERIALS_HPP