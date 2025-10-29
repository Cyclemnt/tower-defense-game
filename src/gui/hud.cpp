#include <iostream>
#include <iomanip>
#include <sstream>
#include "../../include/gui/hud.hpp"
#include "../../include/renderer/renderer.hpp"
#include "../../include/resources/materials.hpp"

HUD::HUD(const RenderContext& ctx_, const Game& game_)
    : ctx(ctx_), game(game_)
{
    if (!font.openFromFile("../assets/gui/arial.ttf")) {
        std::cerr << "[HUD] Failed to load font ../assets/arial.ttf\n";
    }
}

void HUD::draw(float deltaTime) {
    // Throttle FPS update (every 0.25s)    
    if (fpsClock.getElapsedTime().asSeconds() > 0.25f) {
        if (deltaTime > 1e-6f) lastFPS = 1.0f / deltaTime;
        fpsClock.restart();
    }

    // Draw a small HUD in top center
    sf::Vector2u win = ctx.window.getSize();
    float panelW = 260.0f;
    float panelH = 92.0f;
    float panelX = (static_cast<float>(win.x) - panelW) * 0.5f;
    float panelY = 8.0f;

    // Panel background
    sf::RectangleShape panel({panelW, panelH});
    panel.setPosition({panelX, panelY});
    panel.setFillColor(sf::Color(0, 0, 0, 150));
    panel.setOutlineThickness(2.0f);
    panel.setOutlineColor(sf::Color(80, 80, 80));
    ctx.window.draw(panel);

    // Draw components
    drawResources();
    drawCores({panelX + 10.0f, panelY + 58.0f}, panelW - 20.0f);
    drawWaveInfo({panelX + 10.0f, panelY + 36.0f});
    drawFPS({10.0f, 10.0f});
}

void HUD::drawResources() const {
    const Materials::Quantities mats = game.getPlayer().getBalance();
    // icon positions
    float baseX = (ctx.window.getSize().x - 260.0f) * 0.5f + 12.0f;
    float baseY = 16.0f;
    const float iconSize = 20.0f;

    struct IconInfo  { const char* file; unsigned int value; const char* name; };
    IconInfo resources[3] = {
        { "icon_gold.png", mats.au, "Au" },
        { "icon_silver.png", mats.ag, "Ag" },
        { "icon_copper.png", mats.cu, "Cu" }
    };

    for (int i = 0; i < 3; ++i) {
        const sf::Texture& tex = ctx.renderer.getTexture(std::string(resources[i].file));
        sf::Sprite icon(tex);
        sf::Vector2u sz = tex.getSize();
        icon.setScale({iconSize / static_cast<float>(sz.x), iconSize / static_cast<float>(sz.y)});
        icon.setPosition({baseX + i * 80.0f, baseY});
        ctx.window.draw(icon);

        // Value
        sf::Text txt(font, std::to_string(resources[i].value), 16);
        txt.setFillColor(sf::Color::White);
        txt.setPosition({baseX + i * 80.0f + 26.0f, baseY - 2.0f});
        ctx.window.draw(txt);
    }
}

void HUD::drawCores(sf::Vector2f position, float width) const {
    Cores cores = game.getCores();
    const unsigned int safe = cores.getSafe();
    const unsigned int stolen = cores.getStolen();
    const unsigned int lost = cores.getLost();
    const unsigned int total = safe + stolen + lost;
    if (total == 0) return;

    const float spacing = 4.0f;
    const int maxPerRow = 12;
    const float rectHeight = 10.0f;
    float rectWidth = (width - (maxPerRow - 1) * spacing) / maxPerRow;
    float totalWidth = maxPerRow * (rectWidth + spacing) - spacing;
    float startX = position.x + (width - totalWidth) * 0.5f;
    
    float curX = startX, curY = position.y;
    int col = 0;

    // Draw cores
    for (int idx = 0; idx < total; ++idx) {
        if (col >= maxPerRow) { 
            col = 0;
            curY += rectHeight + spacing;
            curX = startX;
        }
        
        sf::RectangleShape rect({rectWidth, rectHeight});
        rect.setPosition({curX, curY});

        if (idx < safe) rect.setFillColor(sf::Color(0,150,255)); // Blue for safe
        else if (idx < safe + stolen) rect.setFillColor(sf::Color(255,140,0)); // Orange for stolen
        else rect.setFillColor(sf::Color(200,50,50)); // Red for lost

        ctx.window.draw(rect);
        curX += rectWidth + spacing;
        ++col;
    }
}

void HUD::drawWaveInfo(sf::Vector2f position) const {
    int currentWave = 5;
    int totalWaves = 10;
    float timeToNext = 50.0f;

    // TO IMPLEMENT:
    // const auto& wm = game_.getWaveManager();
    // currentWave = wm.getCurrentWave();
    // totalWaves  = wm.getTotalWaves();
    // timeToNext  = wm.getTimeUntilNextWave();

    // OR:
    // currentWave = game.getCurrentWave();
    // totalWaves  = game.getTotalWaves();
    // timeToNext  = game.getTimeUntilNextWave();

    std::ostringstream ss;
    if (totalWaves > 0)
        ss << "Wave: " << currentWave << " / " << totalWaves;
    else
        ss << "Wave: " << currentWave;

    if (timeToNext < 0.01f || timeToNext > 9999.0f) {
        ss << "  Next: 0.0s";
    } else {
        ss << "  Next: " << std::fixed << std::setprecision(1) << timeToNext << "s";
    }

    sf::Text txt(font, ss.str(), 14);
    txt.setFillColor(sf::Color::White);
    txt.setPosition(position);
    ctx.window.draw(txt);
}

void HUD::drawFPS(sf::Vector2f position) const {
    sf::Text txt(font, "FPS: " + std::to_string((int) lastFPS), 14);
    txt.setFillColor(sf::Color::White);
    txt.setPosition(position);
    ctx.window.draw(txt);
}
