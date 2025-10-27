#ifndef GATLING_HPP
#define GATLING_HPP

#include <SFML/System/Vector2.hpp>
#include "tower.hpp"

/**
 * @class Gatling
 * @brief Rapid-fire, low-damage tower ideal against swarms.
 */
class Gatling final : public Tower {
public:
    explicit Gatling(sf::Vector2i position_) noexcept;
    ~Gatling() override = default;

protected:
    [[nodiscard]] std::string getTextureName(int frame) const override;
};

#endif // GATLING_HPP
