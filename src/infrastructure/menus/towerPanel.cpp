#include "infrastructure/menus/towerPanel.hpp"
#include <iostream>
namespace tdg::infra {
    
    TowerPanel::TowerPanel(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<float> tileSize)
        : m_window(window), m_tileSize(tileSize)
    {
        m_towerNames = {"Gatling", "Mortar", "Laser"};
        m_towerPanels.push_back(sf::FloatRect());
        m_towerPanels.push_back(sf::FloatRect());
        m_towerPanels.push_back(sf::FloatRect());
    }

    bool TowerPanel::handleClick(const sf::Vector2i& mousePos) {
        // Sell button
        if (m_sellRect.contains({(float)mousePos.x, (float)mousePos.y})) {
            m_mode = (m_mode == Mode::Sell) ? Mode::None : Mode::Sell;
            return true;
        }
        // Upgrade button
        if (m_upgradeRect.contains({(float)mousePos.x, (float)mousePos.y})) {
            m_mode = (m_mode == Mode::Upgrade) ? Mode::None : Mode::Upgrade;
            return true;
        }

        // Tower buttons
        for (size_t i = 0; i < m_towerPanels.size(); ++i) {
            if (m_towerPanels[i].contains({(float)mousePos.x, (float)mousePos.y})) {
                bool affordable = onCanAffordRequest(m_towerNames[i]);
                if (!affordable) return true;
                switch (i) {
                    case 0: m_mode = (m_mode == Mode::Gatling) ? Mode::None : Mode::Gatling; break;
                    case 1: m_mode = (m_mode == Mode::Mortar) ? Mode::None : Mode::Mortar; break;
                    case 2: m_mode = (m_mode == Mode::Laser) ? Mode::None : Mode::Laser; break;
                    default: break;
                }
                return true;
            }
        }
        return false;
    }

    void TowerPanel::handleTileClick(const sf::Vector2i& tilePos) {
        if (m_mode == Mode::Sell) {
            onSellRequest(tilePos.x, tilePos.y);
            return;
        }
        if (m_mode == Mode::Upgrade) {
            onUpgradeRequest(tilePos.x, tilePos.y);
            return;
        }
        switch (m_mode) {
            case Mode::Gatling: onBuildRequest("Gatling", tilePos.x, tilePos.y); break;
            case Mode::Mortar: onBuildRequest("Mortar", tilePos.x, tilePos.y); break;
            case Mode::Laser: onBuildRequest("Laser", tilePos.x, tilePos.y); break;
            default: break;
        }
    }

    void TowerPanel::handleMouseMove(const sf::Vector2i& tilePos) {
        if (onTileOpenRequest(tilePos.x, tilePos.y)) {
            m_tileOverlay = sf::RectangleShape({*m_tileSize, *m_tileSize});
            m_tileOverlay.setPosition({static_cast<float>(tilePos.x) * *m_tileSize, static_cast<float>(tilePos.y) * *m_tileSize});

            if (onTowerAtRequest(tilePos.x, tilePos.y)) {
                switch (m_mode) {
                    case Mode::Sell: m_tileOverlay.setFillColor(sf::Color(255,50,50,80)); break;
                    case Mode::Upgrade: m_tileOverlay.setFillColor(sf::Color(255,160,50,80)); break;
                    case Mode::None: m_tileOverlay.setFillColor(sf::Color(50,50,50,80)); break;
                    default: m_tileOverlay.setFillColor(sf::Color(50,50,50,80)); break;
                }
                if (m_mode == Mode::None) {
                    float radius = onTowerRangeRequest(tilePos.x, tilePos.y).value() * *m_tileSize;
                    m_towerRangeOverlay = sf::CircleShape(radius);
                    m_towerRangeOverlay.setPosition({(static_cast<float>(tilePos.x) + 0.5f) * *m_tileSize - radius, (static_cast<float>(tilePos.y) + 0.5f) * *m_tileSize - radius});
                    m_towerRangeOverlay.setFillColor(sf::Color(0, 0, 0, 0));
                    m_towerRangeOverlay.setOutlineThickness(m_scale * 5.0f);
                    m_towerRangeOverlay.setOutlineColor(sf::Color(110, 175, 255, 127));
                }
            } else {
                switch (m_mode) {
                    case Mode::Sell: m_tileOverlay.setFillColor(sf::Color(50,50,50,80)); break;
                    case Mode::Upgrade: m_tileOverlay.setFillColor(sf::Color(50,50,50,80)); break;
                    case Mode::None: m_tileOverlay.setFillColor(sf::Color(50,50,50,80)); break;
                    default: m_tileOverlay.setFillColor(sf::Color(50,200,50,80)); break;
                }
            m_towerRangeOverlay.setFillColor(sf::Color(0,0,0,0));
            m_towerRangeOverlay.setOutlineColor(sf::Color(0,0,0,0));
            }
        } else {
            m_towerRangeOverlay.setFillColor(sf::Color(0,0,0,0));
            m_towerRangeOverlay.setOutlineColor(sf::Color(0,0,0,0));
            m_tileOverlay.setFillColor(sf::Color(0,0,0,0));
        }
    }

    void TowerPanel::draw(core::IVideoRenderer& vidRenderer) {
        m_winX = vidRenderer.getWindowWidth();
        m_winY = vidRenderer.getWindowHeight();
        m_scale = static_cast<float>(m_winX) / 1920.0f; // base scale from 1080p reference

        drawBackPanel(vidRenderer);
        drawTowerButtons(vidRenderer);
        drawUpgradeBtn(vidRenderer);
        drawSellBtn(vidRenderer);
    }

    void TowerPanel::drawOverlays(core::IVideoRenderer& vidRenderer) {
        m_winX = vidRenderer.getWindowWidth();
        m_winY = vidRenderer.getWindowHeight();
        m_scale = static_cast<float>(m_winX) / 1920.0f; // base scale from 1080p reference

        m_window->draw(m_tileOverlay);
        m_window->draw(m_towerRangeOverlay);
    }

    void TowerPanel::drawBackPanel(core::IVideoRenderer& vidRenderer) {
        float panelW = 356 * m_scale;
        float panelH = 302 * m_scale;
        float panelX = 10.0f * m_scale;
        float panelY = m_winY - panelH - 10.0f * m_scale;
        m_backPanel = sf::FloatRect({panelX, panelY}, {panelW, panelH});

        vidRenderer.drawRectangle(panelX, panelY, panelW, panelH, {0u,0u,0u,160u}, 2.0f, {60u,60u,60u}, false);
    }

    void TowerPanel::drawTowerButtons(core::IVideoRenderer& vidRenderer) {
        const float margin = 10.0f * m_scale;
        const float lineH = (m_backPanel.size.y - 86.0f * m_scale) / 3.0f - margin * 0.5f;
        const float iconSize = lineH * 0.7f;

        std::string towerIconNames[3] = {"icons/gatling", "icons/mortar", "icons/laser"};
        std::string matsIconNames[3] = {"icons/gold", "icons/silver", "icons/copper"};

        for (size_t i = 0; i < 3; ++i) {
            bool affordable = onCanAffordRequest(m_towerNames[i]);

            const float btnW = m_backPanel.size.x - 2 * margin;
            const float btnH = lineH - 5.0f * m_scale;
            const float btnX = m_backPanel.position.x + margin;
            const float btnY = m_backPanel.position.y + margin + i * (btnH + margin * 0.5f);
            m_towerPanels[i] = sf::FloatRect({btnX, btnY}, {btnW, btnH});

            utils::Color fill;
            if (m_mode == Mode::Sell) fill = {150u,60u,60u,150u};
            else if (m_mode == Mode::Upgrade) fill = {145u,150u,60u,150u};
            else if (m_mode == Mode::Gatling && i == 0) fill = {200u,180u,60u,160u};
            else if (m_mode == Mode::Mortar && i == 1) fill = {200u,180u,60u,160u};
            else if (m_mode == Mode::Laser && i == 2) fill = {200u,180u,60u,160u};
            else if (affordable) fill = {80u,80u,80u,180u};
            else fill = {50u,50u,50u,100u};

            
            if (m_mode == Mode::Gatling && i == 0 && !affordable) m_mode = Mode::None;
            else if (m_mode == Mode::Mortar && i == 1 && !affordable) m_mode = Mode::None;
            else if (m_mode == Mode::Laser && i == 2 &&  !affordable) m_mode = Mode::None;

            const float thickness = 1.5f * m_scale;

            vidRenderer.drawRectangle(btnX, btnY, btnW, btnH, fill, thickness, {90u,90u,90u}, false);

            // Tower icon
            const float iconX = btnX + 6.0f * m_scale;
            const float iconY = btnY + (btnH - iconSize) * 0.5f;

            utils::Color spriteColor = {0u,0u,0u,0u};
            if (!affordable) spriteColor.setColor(150u,150u,150u,150u);
            vidRenderer.drawSprite(towerIconNames[i], iconX, iconY, iconSize, spriteColor, false);

            // Tower name
            utils::Color text;
            if (onCanAffordRequest(m_towerNames[i])) text = {255u,255u,255u,255u};
            else text = {140u,140u,140u,255u};
            vidRenderer.drawText(m_towerNames[i], 18.0f * m_scale, btnX + iconSize + 16.0f * m_scale, btnY + 4.0f * m_scale, {255u,255u,255u}, false);

            // Costs

            float costX = btnX + iconSize + 16.0f * m_scale;
            float costY = btnY + lineH * 0.45f;

            const float costIconSize = 20.0f * m_scale;
            const float spacing = 80.0f * m_scale;

            std::optional<core::Materials> cost = onCostRequest(m_towerNames[i]);
            if (!cost.has_value()) return;

            std::vector<unsigned int> costButInAVector = {cost.value().au, cost.value().ag, cost.value().cu};

            for (int j = 0; j < 3; ++j) {
                utils::Color costIconColor = {255u,255u,255u,255u};
                if (!affordable) costIconColor.setColor(150u,150u,150u,150u);
                vidRenderer.drawSprite(matsIconNames[j], costX, costY, costIconSize, costIconColor, false);
                vidRenderer.drawText(std::to_string(costButInAVector[j]), 16*m_scale, costX + 26.0f * m_scale, costY - 2.0f * m_scale, costIconColor, false);
                costX += spacing;
            }
        }
    }

    void TowerPanel::drawUpgradeBtn(core::IVideoRenderer& vidRenderer) {
        const float margin = 10.0f * m_scale;
        const float btnW = m_backPanel.size.x - 2.0f * margin;
        const float btnH = 28.0f * m_scale;
        const float btnX = m_backPanel.position.x + margin;
        const float btnY = m_backPanel.position.y + m_backPanel.size.y - 2.0f * btnH - 2.0f * margin;
        const float btnThickness = 1.5f * m_scale;

        m_upgradeRect = sf::FloatRect({btnX, btnY}, {btnW, btnH});

        utils::Color fill;
        if (m_mode == Mode::Upgrade) fill = {195u,200u,80u,180u};
        else fill = {115u,120u,40u,150u};
        vidRenderer.drawRectangle(btnX, btnY, btnW, btnH, fill, btnThickness, {90u,90u,90u,255u}, false);

        // Text
        const float txtSize = 16.0f * m_scale;
        const float txtX = btnX + 20.0f * m_scale;
        const float txtY = btnY + 3.0f * m_scale;

        vidRenderer.drawText("Upgrade Mode", txtSize, txtX, txtY, {255u,255u,255u,255u}, false);
    }

    void TowerPanel::drawSellBtn(core::IVideoRenderer& vidRenderer) {
        const float margin = 10.0f * m_scale;
        const float btnW = m_backPanel.size.x - 2.0f * margin;
        const float btnH = 28.0f * m_scale;
        const float btnX = m_backPanel.position.x + margin;
        const float btnY = m_backPanel.position.y + m_backPanel.size.y - btnH - margin;
        const float btnThickness = 1.5f * m_scale;

        m_sellRect = sf::FloatRect({btnX, btnY}, {btnW, btnH});

        utils::Color fill;
        if (m_mode == Mode::Sell) fill = {200u,80u,80u,180u};
        else fill = {120u,40u,40u,150u};
        vidRenderer.drawRectangle(btnX, btnY, btnW, btnH, fill, btnThickness, {90u,90u,90u,255u}, false);

        // Text
        const float txtSize = 16.0f * m_scale;
        const float txtX = btnX + 20.0f * m_scale;
        const float txtY = btnY + 3.0f * m_scale;

        vidRenderer.drawText("Sell Mode", txtSize, txtX, txtY, {255u,255u,255u,255u}, false);
    }

    void TowerPanel::setProvider(core::GameViewProvider provider) {
        m_provider = std::move(provider);
    }


} // namespace tdg::infra
