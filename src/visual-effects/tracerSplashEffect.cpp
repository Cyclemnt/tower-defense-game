#include "../../include/visual-effects/tracerSplashEffect.hpp"
#include <cmath>

SplashEffect::SplashEffect(std::array<float, 2> pos, sf::Color c, float duration)
    : position(pos), lifetime(duration), color(c) {}

void SplashEffect::update(float dt) {
    lifetime -= dt;
}

void SplashEffect::render(sf::RenderWindow& w, float tileSize) const {
    if (lifetime > 0) {
        // Créer quelques particules autour du point de splash, mais réduire la portée pour correspondre à la taille de la grille
        for (int i = 0; i < 3; ++i) {
            float angle = std::rand() % 360;
            // Réduire la distance pour un effet plus petit et plus réaliste
            float distance = (std::rand() % 3 + 1) * 0.1f;  // Entre 0.1 et 0.3 (par rapport à la taille d'une créature)
            sf::CircleShape particle(1.0f);  // Petites particules pour simuler l'impact
            particle.setFillColor(color);
            particle.setPosition({
                (position[0] + 0.5f + std::cos(angle) * distance) * tileSize,
                (position[1] + 0.5f + std::sin(angle) * distance) * tileSize
            });
            w.draw(particle);
        }
    }
}

bool SplashEffect::isAlive() const { return lifetime > 0.f; }
