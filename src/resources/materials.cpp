#include "../../include/resources/materials.hpp"

#include <stdexcept>

Materials::Materials()
    : au(1000), ag(1000), cu(1000) {}

Materials::~Materials() {}

std::array<int, 3> Materials::getBalance() const {
    return {au, ag, cu};
}

void Materials::add(std::array<int, 3> amounts) {
    if (amounts[0] < 0) throw std::runtime_error("Trying to add a negative amount of Au");
    if (amounts[1] < 0) throw std::runtime_error("Trying to add a negative amount of Ag");
    if (amounts[2] < 0) throw std::runtime_error("Trying to add a negative amount of Cu");
    au += amounts[0];
    ag += amounts[1];
    cu += amounts[2];
}

void Materials::spend(std::array<int, 3> amounts) {
    if (amounts[0] > au || amounts[0] < 0) throw std::runtime_error("Trying to spend an incorect amount of Au");
    if (amounts[1] > ag || amounts[1] < 0) throw std::runtime_error("Trying to spend an incorect amount of Ag");
    if (amounts[2] > cu || amounts[2] < 0) throw std::runtime_error("Trying to spend an incorect amount of Cu");
    au -= amounts[0];
    ag -= amounts[1];
    cu -= amounts[2];
}
