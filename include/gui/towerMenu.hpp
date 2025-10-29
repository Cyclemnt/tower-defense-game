#ifndef TOWER_MENU_HPP
#define TOWER_MENU_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "menu.hpp"
#include "../game.hpp"
#include "../renderer/renderContext.hpp"

/**
 * @class TowerMenu
 * @brief Contextual menu opened on buildable tiles.
 *
 * Shows either build options (if tile empty) or sell option (if occupied).
 * Uses small helper builders for clarity.
 */
class TowerMenu final : public Menu {
private:
    bool occupied = false;
    sf::Vector2i tilePos = {0, 0};

    void buildBasePanel();
    void buildBuildPanel();
    void buildSellPanel();
    void addCancelButton();
    void addTowerButton(const std::string& name, std::function<std::unique_ptr<Tower>(sf::Vector2i)> factory,
                        const std::string& cost, float y);

    // Utilities
    void showError(const std::string& message);
    void scheduleRemoveWidget(tgui::Widget::Ptr widget, unsigned int ms);

public:
    TowerMenu(tgui::Gui& gui, Game& game, const RenderContext& ctx) noexcept;
    void open(const sf::Vector2i& tilePos_, bool occupied_);
    void open() override {}
};

#endif // TOWER_MENU_HPP
