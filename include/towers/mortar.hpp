#ifndef MORTAR_HPP
#define MORTAR_HPP

#include "tower.hpp"

class Mortar : public Tower
{
private:
    struct Shell {
        float posX, posY;
        float targetX, targetY;
        float damage;
        float speed = 4.0f;  // tiles per second
        float explosionRadius = 0.4f;
        bool active = true;
    };

    std::vector<Shell> shells;

public:
    Mortar(int x_, int y_);
    ~Mortar();
    void update(float deltaTime, const std::vector<std::unique_ptr<Creature>>& creatures) override;
    std::string getTypeName() const override;
};

#endif // MORTAR_HPP
