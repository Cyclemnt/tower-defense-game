#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <SFML/Graphics.hpp>
#include "pauseMenu.hpp"
#include "towerMenu.hpp"
#include "../game.hpp"
#include "../renderer/renderContext.hpp"
#include "hud.hpp"

class Game;
class Renderer;


class GuiManager {
private:
    tgui::Gui gui;
    Game& game;
    RenderContext& ctx;
    HUD hud;

    PauseMenu pauseMenu;
    TowerMenu towerMenu;

    void handleLeftClick(int mouseX, int mouseY);

public:
    GuiManager(sf::RenderWindow& window, Game& game, RenderContext& ctx);

    void processEvent(const sf::Event& event);
    void draw(float deltaTime);
};

#endif // GUIMANAGER_HPP
