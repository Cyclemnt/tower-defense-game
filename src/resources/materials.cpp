#include "../../include/resources/materials.hpp"

Materials::Materials()
    : au(0), ag(0), cu(0) {}

Materials::~Materials() {}

void Materials::add(std::array<int, 3> amounts) {
}

void Materials::spend(std::array<int, 3> amounts) {
}

bool Materials::canAfford(Tower t) const {
    return false;
}
