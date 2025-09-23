#include "../../include/resources/materials.hpp"

Materials::Materials()
    : au(10), ag(0), cu(0) {}

Materials::~Materials() {}

std::array<int, 3> Materials::getBalance() const {
    return {au, ag, cu};
}

void Materials::add(std::array<int, 3> amounts) {
}

void Materials::spend(std::array<int, 3> amounts) {
}
