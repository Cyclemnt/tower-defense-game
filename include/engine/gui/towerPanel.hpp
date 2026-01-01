#ifndef TOWER_PANEL_HPP
#define TOWER_PANEL_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <SFML/Graphics.hpp>

namespace tdg::engine { class IGame; class CommandBus; }
namespace tdg::core { class IVideoRenderer; }

namespace tdg::engine {

    class TowerPanel {
    public:
        enum class Mode { None, Sell, Upgrade, Gatling, Mortar, Laser };
        
        TowerPanel(std::shared_ptr<float> tileSize, std::shared_ptr<CommandBus> bus);

        void draw(core::IVideoRenderer& vidRenderer);
        void drawOverlays(core::IVideoRenderer& vidRenderer);
    
        bool handleClick(const sf::Vector2i& mousePos);
        void handleTileClick(const sf::Vector2i& tilePos);
        void handleMouseMove(const sf::Vector2i& tilePos);

        void setGamePtr(std::weak_ptr<IGame> game);

    private:
        void drawBackPanel(core::IVideoRenderer& vidRenderer);
        void drawTowerButtons(core::IVideoRenderer& vidRenderer);
        void drawUpgradeBtn(core::IVideoRenderer& vidRenderer);
        void drawSellBtn(core::IVideoRenderer& vidRenderer);
        
        std::shared_ptr<float> m_tileSize{nullptr};

        std::weak_ptr<IGame> m_game;
        std::shared_ptr<CommandBus> m_bus;

        Mode m_mode{Mode::None};

        sf::RectangleShape m_tileOverlay;
        sf::CircleShape m_towerRangeOverlay;

        sf::FloatRect m_backPanel;
        sf::FloatRect m_sellRect;
        sf::FloatRect m_upgradeRect;
        std::vector<sf::FloatRect> m_towerPanels;
        std::vector<std::string> m_towerNames;
    };

} // namespace tdg::engine

#endif // TOWER_PANEL_HPP