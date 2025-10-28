#ifndef MORTAR_HPP
#define MORTAR_HPP

#include <SFML/System/Vector2.hpp>
#include "tower.hpp"

/**
 * @class Mortar
 * @brief Area-of-effect tower that fires explosive shells.
 */
class Mortar final : public Tower {
public:
    /// @brief Represents a projectile fired by the Mortar.
    struct Shell {
        sf::Vector2f position;
        sf::Vector2f target;
        float damage;
        float speed = 4.0f;
        float explosionRadius = 0.6f;
        bool active = true;
    };

private:
    std::vector<Shell> shells;

public:
    explicit Mortar(sf::Vector2i position_) noexcept;
    ~Mortar() override = default;

    void update(float deltaTime, const std::vector<std::unique_ptr<Creature>>& creatures) override;

    [[nodiscard]] const std::vector<Shell>& getShells() const noexcept { return shells; }

protected:
    [[nodiscard]] std::string getTextureName(int frame) const override;
};

#endif // MORTAR_HPP
