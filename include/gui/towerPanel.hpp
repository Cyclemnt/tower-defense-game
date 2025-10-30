#ifndef TOWER_PANEL_HPP
#define TOWER_PANEL_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <functional>
#include "../renderer/renderContext.hpp"
#include "../game.hpp"
#include "../towers/tower.hpp"
#include "../towers/gatling.hpp"
#include "../towers/laser.hpp"
#include "../towers/mortar.hpp"

/**
 * @class TowerPanel
 * @brief Displays a responsive tower selection panel at the bottom-left of the screen.
 *
 * Towers are displayed with their icon, name, and cost (using resource icons for Au, Ag, Cu).
 * The player can select a tower to build it by clicking on a free OpenZone tile.
 * A "Sell" mode allows selling existing towers directly by clicking them.
 */
class TowerPanel {
private:
    struct TowerEntry {
        std::string name;                                   ///< Tower name
        std::string textureName;                            ///< Tower icon
        Materials::Quantities cost;                         ///< Price (Au, Ag, Cu)
        std::function<std::unique_ptr<Tower>(sf::Vector2i)> factory; ///< Factory function
        sf::FloatRect rect;                                 ///< Clickable area
        bool affordable = true;                             ///< True if the player can afford it
    };

    const RenderContext& ctx;
    Game& game;

    sf::Font font;
    std::vector<TowerEntry> entries; /// Every buyable tower (initialized in TowerPanel's constructor)
    sf::FloatRect sellRect;

    int selectedIndex = -1;
    bool sellingMode = false;

    // Cached icons for materials
    const sf::Texture* texGold = nullptr;   ///< Pointer to the gold icon texture
    const sf::Texture* texSilver = nullptr; ///< Pointer to the silver icon texture
    const sf::Texture* texCopper = nullptr; ///< Pointer to the copper icon texture

    // --- Drawing helpers ---
    void updateAffordability();
    sf::FloatRect getPanelRect() const;
    void drawPanel(sf::RenderWindow& win) const;
    void drawTowers(sf::RenderWindow& win);
    void drawSellButton(sf::RenderWindow& win);
    void drawCostIcons(sf::RenderWindow& win, const TowerEntry& e, sf::Vector2f basePos, float iconSize);

public:
    TowerPanel(const RenderContext& ctx_, Game& game_);

    void draw();
    bool handleClick(const sf::Vector2i& mousePos);

    /// @brief Called when the player clicks on a tile in the world.
    /// Depending on mode (build/sell), acts accordingly.
    /// @param tilePos The clicked tile position.
    void handleTileClick(const sf::Vector2i& tilePos);
};

#endif // TOWER_PANEL_HPP
