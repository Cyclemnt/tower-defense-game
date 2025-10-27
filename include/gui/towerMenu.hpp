#ifndef TOWER_MENU_HPP
#define TOWER_MENU_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "menu.hpp"
#include "../game.hpp"
#include "../renderer/renderContext.hpp"

class TowerMenu : public Menu {
private:
    bool occupied = false;
    sf::Vector2i tilePos;

    void buildBasePanel();
    void buildBuildPanel();
    void buildSellPanel();
    void addCancelButton();
    void addTowerButton(const std::string& name,
                        std::function<std::unique_ptr<Tower>(sf::Vector2i)> factory,
                        const std::string& cost,
                        float y);

    void showError(const std::string& message);
    void scheduleRemoveWidget(tgui::Widget::Ptr widget, unsigned int ms);

public:
    TowerMenu(tgui::Gui& gui, Game& gm, RenderContext& ctx);
    void open(sf::Vector2i tilePos, bool occupied);
    void open() override {}
};

#endif // TOWER_MENU_HPP
