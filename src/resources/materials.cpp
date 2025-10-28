#include <stdexcept>
#include "../../include/resources/materials.hpp"

Materials::Materials(Quantities initial) noexcept
    : quantities(initial) {}

void Materials::spend(const Quantities& cost) {
    if (!canAfford(cost)) throw std::runtime_error("Attempting to spend more materials than available.");
    quantities -= cost;
}

[[nodiscard]] bool Materials::canAfford(const Quantities& cost) const noexcept {
    return (quantities.au >= cost.au && quantities.ag >= cost.ag && quantities.cu >= cost.cu);
}