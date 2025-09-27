#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Core.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Widgets/Button.hpp>

#include "game.hpp"

class Renderer {
private:
    sf::RenderWindow window;
    tgui::Gui gui;

    // Textures (tiles, towers, creatures…)
    sf::Texture texPath, texEmpty, texOpen, texEntry, texExit, texCore;
    sf::Texture texTowerGatling, texTowerMortar, texTowerLaser;
    sf::Texture texMinionCreature, texDroneCreature, texTankCreature;
    sf::Texture texNull;

    float tileSize; // Taille en pixels d'une case

public:
    Renderer(int width, int height, int tileSize);

    bool isOpen() const;
    void processEvents(Game& game);
    void render(const Game& game);

private:
    void loadTextures();
    void drawMap(const Game& game);
    void drawTowers(const Game& game);
    void drawCreatures(const Game& game);
    void drawUI(const Game& game);
};


#endif // RENDERER_HPP
