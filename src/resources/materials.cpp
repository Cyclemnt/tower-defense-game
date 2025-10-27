#include <stdexcept>
#include "../../include/resources/materials.hpp"

Materials::Materials(Quantities initial) : quantities(initial) {}

const Materials::Quantities& Materials::getQuantities() const { return quantities; }

void Materials::add(const Quantities& other) { quantities += other; }

void Materials::spend(const Quantities& other) {
    if (canAfford(other)) quantities -= other;
    else throw std::runtime_error("Tring to spend more materials than available");
}

bool Materials::canAfford(const Quantities& costs) const {
    return (quantities.au >= costs.au && quantities.ag >= costs.ag && quantities.cu >= costs.cu);
}