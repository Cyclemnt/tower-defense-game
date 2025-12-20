#include <iostream>
#include <sstream>
#include "infrastructure/menus/hud.hpp"
#include "core/materials.hpp"

namespace tdg::infra {
    
    HUD::HUD() {}

    void HUD::update(float dt) {
        if (m_fpsClock.getElapsedTime().asSeconds() > 1.0f) {
            if (dt > 1e-6f) m_lastFPS = 1.0f / dt;
            m_fpsClock.restart();
        }
    }

    void HUD::draw(core::IVideoRenderer& vidRenderer) {
        if (!m_provider || !m_provider().has_value()) return;
        m_winX = vidRenderer.getWindowWidth();
        m_winY = vidRenderer.getWindowHeight();
        m_scale = static_cast<float>(m_winX) / 1920.0f; // base scale from 1080p reference

        drawResourcesPanel(vidRenderer);
        drawCores(vidRenderer);
        drawWavePanel(vidRenderer);
        drawFPSPanel(vidRenderer);
    }

    void HUD::drawResourcesPanel(core::IVideoRenderer& vidRenderer) const {
        // Panel
        const float panelW = 260.0f * m_scale;
        const float panelH = 92.0f * m_scale;
        const float panelX = (m_winX - panelW) * 0.5f;
        const float panelY = 8.0f * m_scale;

        utils::Color fill = {0, 0, 0, 150};
        float thikness = 2.0f * m_scale;
        utils::Color outline = {80, 80, 80};
        vidRenderer.drawRectangle(panelX, panelY, panelW, panelH, fill, thikness, outline);

        // Resources
        if (!m_provider().has_value()) return;
        const core::Materials mats = m_provider().value().materials; // idk how to proprely get player balance
        const float iconSize = 20.0f * m_scale;
        const float spacing = 80.0f * m_scale;
        const float baseX = panelX + 12.0f * m_scale;
        const float baseY = panelY + 16.0f * m_scale;

        struct Icon { const std::string file; unsigned int value; };
        const Icon resources[3] = {
            {"icons/gold", mats.au},
            {"icons/silver", mats.ag},
            {"icons/copper", mats.cu}
        };

        for (int i = 0; i < 3; ++i) {
            vidRenderer.drawSprite(resources[i].file, baseX + i * spacing, baseY, iconSize);

            float txtSize = 16.0f * m_scale;
            float txtX = baseX + i * spacing + 26.0f * m_scale;
            float txtY = baseY - 2.0f * m_scale;
            utils::Color txtColor = {255u,255u,255u};
            vidRenderer.drawText(std::to_string(resources[i].value), txtSize, txtX, txtY, txtColor);
        }
    }

    void HUD::drawCores(core::IVideoRenderer& vidRenderer) const {
        const float panelW = 240.0f * m_scale;
        const float panelH = 92.0f * m_scale;
        const float panelX = (m_winX - panelW) * 0.5f;
        const float panelY = 66.0f * m_scale;
        
        const unsigned safe = m_provider()->coresSafe;
        const unsigned stolen = m_provider()->coresStolen;
        const unsigned lost = m_provider()->coresLost;
        const unsigned total = safe + stolen + lost;
        if (total == 0) return;

        const float spacing = 4.0f * m_scale;
        const int maxPerRow = 12;
        const float rectHeight = 10.0f * m_scale;
        const float rectWidth = (panelW - (maxPerRow - 1) * spacing) / maxPerRow;
        const float totalWidth = maxPerRow * (rectWidth + spacing) - spacing;
        const float startX = panelX + (panelW - totalWidth) * 0.5f;

        float curX = startX, curY = panelY;
        int i = 0;

        for (unsigned idx = 0; idx < total; ++idx) {
            if (i >= maxPerRow) {
                i = 0;
                curY += rectHeight + spacing;
                curX = startX;
            }

            utils::Color fill;
            if (idx < safe) fill = {0u, 150u, 255u};
            else if (idx < safe + stolen) fill = {255u, 140u, 0u};
            else fill = {200u, 50u, 50u};

            vidRenderer.drawRectangle(curX, curY, rectWidth, rectHeight, fill, 0.0f, {0u,0u,0u,0u});
            curX += rectWidth + spacing;
            ++i;
        }
    }

    void HUD::drawWavePanel(core::IVideoRenderer& vidRenderer) const {
        // Panel
        const float panelW = 200.0f * m_scale;
        const float panelH = 70.0f * m_scale;
        const float panelX = 10.0f * m_scale;
        const float panelY = 8.0f * m_scale;

        utils::Color fill {0u, 0u, 0u, 150u};
        float thickness = 2.0f * m_scale;
        utils::Color outline = {80u, 80u, 80u};

        vidRenderer.drawRectangle(panelX, panelY, panelW, panelH, fill, thickness, outline);

        // Text
        const unsigned int currentWave = m_provider()->currentWave;
        const unsigned int totalWaves = m_provider()->totalWaves;
        const unsigned int timeToNext = m_provider()->timeToNextWave;

        std::string waveInfo;
        if (totalWaves == std::numeric_limits<unsigned int>::max()) waveInfo = "Wave " + std::to_string(currentWave) + " / inf";
        else waveInfo = "Wave " + std::to_string(currentWave) + " / " + std::to_string(totalWaves);
        float waveInfoSize = 16.0f * m_scale;
        float waveInfoX = panelX + 10.0f * m_scale;
        float waveInfoY = panelY + 10.0f * m_scale;
        utils::Color waveInfoColor = {255u, 255u, 255u};
        vidRenderer.drawText(waveInfo, waveInfoSize, waveInfoX, waveInfoY, waveInfoColor);

        std::ostringstream ss;
        if (timeToNext > 0) ss << "Next in " << timeToNext << "s";
        else ss << "Wave active";
        float waveTimerSize = 14.0f * m_scale;
        float waveTimerX = waveInfoX;
        float waveTimerY = waveInfoY + 26.0f * m_scale;
        utils::Color waveTimerColor = {200u, 200u, 200u};
        vidRenderer.drawText(ss.str(), waveTimerSize, waveTimerX, waveTimerY, waveTimerColor);
    }

    void HUD::drawFPSPanel(core::IVideoRenderer& vidRenderer) const {
        // Panel
        const float panelW = 100.0f * m_scale;
        const float panelH = 40.0f * m_scale;
        const float panelX = m_winX - panelW - 10.0f * m_scale;
        const float panelY = 8.0f * m_scale;

        utils::Color fill = {0u, 0u, 0u, 150u};
        float thickness = 2.0f * m_scale;
        utils::Color outline = {80u, 80u, 80u};
        vidRenderer.drawRectangle(panelX, panelY, panelW, panelH, fill, thickness, outline);

        // Text
        std::string fps = "FPS: " + std::to_string(static_cast<int>(m_lastFPS));
        float fpsSize = 16.0f * m_scale;
        float fpsX = panelX + 10.0f * m_scale;
        float fpsY = panelY + 8.0f * m_scale;
        utils::Color fpsColor = {255u, 255u, 255u};
        vidRenderer.drawText(fps, fpsSize, fpsX, fpsY, fpsColor);
    }

    void HUD::setProvider(core::GameViewProvider provider) {
        m_provider = std::move(provider);
    }

} // namespace tdg::infra
