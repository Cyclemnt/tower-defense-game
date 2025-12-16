#include "infrastructure/menus/towerPanel.hpp"

namespace tdg::infra {
    
    TowerPanel::TowerPanel() {}

    void TowerPanel::draw(core::IVideoRenderer& vidRenderer) {
        m_winX = vidRenderer.getWindowWidth();
        m_winY = vidRenderer.getWindowHeight();
        m_scale = static_cast<float>(m_winX) / 1920.0f; // base scale from 1080p reference

        drawBackPanel(vidRenderer);
        drawTowers(vidRenderer);
        drawCosts(vidRenderer);
        drawUpgradeBtn(vidRenderer);
        drawSellBtn(vidRenderer);
    }

    void TowerPanel::drawBackPanel(core::IVideoRenderer& vidRenderer) {
        m_panelW = 356 * m_scale;
        m_panelH = 302 * m_scale;
        m_panelX = 10.0f * m_scale;
        m_panelY = m_winY - m_panelH - 10.0f * m_scale;
        vidRenderer.drawRectangle(m_panelX, m_panelY, m_panelW, m_panelH, {0u,0u,0u,160u}, 2.0f, {60u,60u,60u}, false);
    }

    void TowerPanel::drawTowers(core::IVideoRenderer& vidRenderer) {
        const float margin = 10.0f * m_scale;
        const float lineH = (m_panelH - 86.0f * m_scale) / 3.0f - margin * 0.5f;
        const float iconSize = lineH * 0.7f;

        std::string iconNames[3] = {"icons/gatling", "icons/mortar", "icons/laser"};
        std::string names[3] = {"Gatling", "Mortar", "Laser"};

        for (size_t i = 0; i < 3; ++i) {
            const float btnW = m_panelW - 2 * margin;
            const float btnH = lineH - 5.0f * m_scale;
            const float btnX = m_panelX + margin;
            const float btnY = m_panelY + margin + i * (btnH + margin * 0.5f);

            utils::Color fill = {80u,80u,80u,180u};
            // if (sellingMode) fill = {150u,60u,60u,150u};
            // else if ((int)i == selectedIndex) fill = {200u,180u,60u,160u};
            // else if (e.affordable) fill = {80u,80u,80u,180u};
            // else fill = {50u,50u,50u,100u};

            const float thickness = 1.5f * m_scale;

            vidRenderer.drawRectangle(btnX, btnY, btnW, btnH, fill, thickness, {90u,90u,90u}, false);

            // Tower icon
            const float iconX = btnX + 6.0f * m_scale;
            const float iconY = btnY + (btnH - iconSize) * 0.5f;

            // if (!e.affordable) sprite.setColor(sf::Color(150, 150, 150, 150));
            vidRenderer.drawSprite(iconNames[i], iconX, iconY, iconSize, false);

            // Tower name
            utils::Color text = {255u,255u,255u,255u};
            // if (affordable) text = {255u,255u,255u,255u};
            // else text = {140u,140u,140u,255u};
            vidRenderer.drawText(names[i], 18.0f * m_scale, btnX + iconSize + 16.0f * m_scale, btnY + 4.0f * m_scale, {255u,255u,255u}, false);
        }
    }

    void TowerPanel::drawCosts(core::IVideoRenderer& vidRenderer) {

    }

    void TowerPanel::drawUpgradeBtn(core::IVideoRenderer& vidRenderer) {
        const float margin = 10.0f * m_scale;
        const float btnW = m_panelW - 2.0f * margin;
        const float btnH = 28.0f * m_scale;
        const float btnX = m_panelX + margin;
        const float btnY = m_panelY + m_panelH - 2.0f * btnH - 2.0f * margin;
        const float btnThickness = 1.5f * m_scale;

        utils::Color fill = {195u,200u,80u,180u};
        // if (sellingMode) fill = {200u,80u,80u,180u};
        // else fill = {120u,40u,40u,150u};
        vidRenderer.drawRectangle(btnX, btnY, btnW, btnH, fill, btnThickness, {90u,90u,90u,255u}, false);

        // Text
        const float txtSize = 16.0f * m_scale;
        const float txtX = btnX + 20.0f * m_scale;
        const float txtY = btnY + 3.0f * m_scale;

        vidRenderer.drawText("Upgrade Mode", txtSize, txtX, txtY, {255u,255u,255u,255u}, false);
    }

    void TowerPanel::drawSellBtn(core::IVideoRenderer& vidRenderer) {
        const float margin = 10.0f * m_scale;
        const float btnW = m_panelW - 2.0f * margin;
        const float btnH = 28.0f * m_scale;
        const float btnX = m_panelX + margin;
        const float btnY = m_panelY + m_panelH - btnH - margin;
        const float btnThickness = 1.5f * m_scale;

        utils::Color fill = {200u,80u,80u,180u};
        // if (sellingMode) fill = {200u,80u,80u,180u};
        // else fill = {120u,40u,40u,150u};
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
