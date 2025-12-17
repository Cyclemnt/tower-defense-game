#ifndef TOWER_PANEL_HPP
#define TOWER_PANEL_HPP

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <SFML/Graphics.hpp>
#include "core/interfaces/iVideoRenderer.hpp"
#include "core/gameViewProvider.hpp"

namespace tdg::infra {


    class TowerPanel {
    public:
        enum class Mode { None, Sell, Upgrade, Gatling, Mortar, Laser };
        
        TowerPanel(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<float> tileSize);

        void draw(core::IVideoRenderer& vidRenderer);
        void drawOverlays(core::IVideoRenderer& vidRenderer);
    
        void setProvider(core::GameViewProvider provider);

        /* I'm sorry. */
        bool handleClick(const sf::Vector2i& mousePos);
        void handleTileClick(const sf::Vector2i& tilePos);
        void handleMouseMove(const sf::Vector2i& tilePos);

        std::function<void(std::string towerType, int tx,int ty)> onBuildRequest;
        std::function<void(int tx,int ty)> onUpgradeRequest;
        std::function<void(int tx,int ty)> onSellRequest;

        std::function<std::optional<float>(int tx, int ty)> onTowerRangeRequest;
        std::function<bool(std::string towerType)> onCanAffordRequest;
        std::function<bool(int tx, int ty)> onTileOpenRequest;
        std::function<bool(int tx, int ty)> onTowerAtRequest;
        std::function<std::optional<core::Materials>(std::string towerType)> onCostRequest;
        /* ========== */

    private:
        void drawBackPanel(core::IVideoRenderer& vidRenderer);
        void drawTowerButtons(core::IVideoRenderer& vidRenderer);
        void drawUpgradeBtn(core::IVideoRenderer& vidRenderer);
        void drawSellBtn(core::IVideoRenderer& vidRenderer);
        
        float m_scale{0.0f};
        std::shared_ptr<float> m_tileSize{nullptr};
        std::shared_ptr<sf::RenderWindow> m_window;
        unsigned int m_winX{0u};
        unsigned int m_winY{0u};

        sf::FloatRect m_backPanel;
        sf::FloatRect m_sellRect;
        sf::FloatRect m_upgradeRect;
        std::vector<sf::FloatRect> m_towerPanels;
        std::vector<std::string> m_towerNames;
        
        /* shouldn't be here */
        sf::RectangleShape m_tileOverlay;
        sf::CircleShape m_towerRangeOverlay;
        /* ================= */
        
        core::GameViewProvider m_provider;

        Mode m_mode{Mode::None};
    };

} // namespace tdg::infra

#endif // TOWER_PANEL_HPP