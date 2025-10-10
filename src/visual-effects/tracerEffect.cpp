#include "../../include/visual-effects/tracerEffect.hpp"
#include "../../include/visual-effects/tracerSplashEffect.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>

TracerEffect::TracerEffect(std::array<float, 2> s, std::array<float, 2> e, float duration)
    : start(s), end(e), lifetime(duration) {}

void TracerEffect::update(float dt) { lifetime -= dt; }

void TracerEffect::render(sf::RenderWindow& w, float tileSize) const {
    // Générer une couleur aléatoire pour chaque segment
    sf::Color randomColor = generateRandomColor();

    // Calcul de la distance totale entre start et end
    float dx = end[0] - start[0];
    float dy = end[1] - start[1];
    float distance = std::sqrt(dx * dx + dy * dy);

    // Choisir un point aléatoire sur la ligne entre start et end
    float randomFactor = std::rand() % 1000 * 0.001f;  // Un facteur aléatoire entre 0 et 1
    float offsetX = dx * randomFactor;
    float offsetY = dy * randomFactor;

    // Position de départ du segment aléatoire avec variation aléatoire
    float randomOffsetStartX = (std::rand() % 200) * 0.001f - 0.1f;  // Petit décalage pour l'effet
    float randomOffsetStartY = (std::rand() % 200) * 0.001f - 0.1f;

    sf::Vector2f randomStartPosition = { start[0] + offsetX + randomOffsetStartX * 0.5f, start[1] + offsetY + randomOffsetStartY };

    // Dessiner un segment avec une longueur fixe
    float segmentLength = 0.4f;  // Longueur du segment, ajustée pour éviter qu'elle dépasse
    float segmentDistance = std::min(segmentLength, distance * (1 - randomFactor));  // Limite la longueur pour ne pas dépasser la cible

    // Normaliser la direction (dx, dy) pour calculer le segment
    float normFactor = segmentDistance / distance;  // On veut une longueur proportionnelle à la distance
    float finalX = randomStartPosition.x + dx * normFactor;
    float finalY = randomStartPosition.y + dy * normFactor;

    // Créer le segment à afficher
    std::array<sf::Vertex, 2> segment;

    segment[0].position = { (randomStartPosition.x + 0.5f) * tileSize, (randomStartPosition.y + 0.5f) * tileSize };
    segment[1].position = { (finalX + 0.5f) * tileSize, (finalY + 0.5f) * tileSize };

    segment[0].color = randomColor;
    segment[1].color = randomColor;

    // Dessiner le segment
    w.draw(segment.data(), segment.size(), sf::PrimitiveType::Lines);

    // Ajouter l'effet de splash à la position de la créature (end)
    SplashEffect splash({end[0], end[1]}, randomColor); // Splash toujours à la position de la créature
    splash.render(w, tileSize);
}

sf::Color TracerEffect::generateRandomColor() const {
    int r = std::min(255, 255 - std::rand() % 100); // Légèrement rouge
    int g = std::min(255, 255 - std::rand() % 100); // Jaune et vert
    int b = 0; // Pas de bleu
    return sf::Color(r, g, b);
}

bool TracerEffect::isAlive() const { return lifetime > 0.f; }