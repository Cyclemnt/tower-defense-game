#include <stdexcept>
#include "../../include/resources/materials.hpp"

Materials::Materials(std::array<unsigned int, 3> materials_)
    : materials{materials_} {}

Materials::~Materials() {}

std::array<unsigned int, 3> Materials::getBalance() const {
    return materials;
}

void Materials::add(std::array<unsigned int, 3> amounts) {
    for (size_t i = 0; i < materials.size(); ++i)
        materials[i] += amounts[i];
}

void Materials::spend(std::array<unsigned int, 3> amounts) {
    for (size_t i = 0; i < materials.size(); ++i)
        materials[i] -= amounts[i];
}
