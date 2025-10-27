#include <iostream>
#include <array>
#include <cmath>
#include "../../include/gui/hud.hpp"
#include "../../include/renderer/renderer.hpp"
#include "../../include/resources/materials.hpp"

HUD::HUD(RenderContext& ctx_, Game& game_)
    : ctx(ctx_), game(game_)
{
    if (!font.openFromFile("../assets/gui/arial.ttf")) {
        std::cerr << "[HUD] Could not load font ../assets/arial.ttf\n";
    }
}

void HUD::draw(float deltaTime) {
    // Update FPS every 0.25s
    if (fpsClock.getElapsedTime().asSeconds() > 0.25f) {
        if (deltaTime > 1e-6f) lastFPS = 1.0f / deltaTime;
        fpsClock.restart();
    }

    // Draw a small HUD in top center
    sf::Vector2u win = ctx.window.getSize();
    float panelW = 260.0f;
    float panelH = 92.0f;
    float panelX = (win.x - panelW) * 0.5f;
    float panelY = 8.0f;

    // panel
    sf::RectangleShape panel({panelW, panelH});
    panel.setPosition({panelX, panelY});
    panel.setFillColor(sf::Color(0,0,0,150));
    panel.setOutlineThickness(2.0f);
    panel.setOutlineColor(sf::Color(80,80,80));
    ctx.window.draw(panel);

    drawResources();

    // cores area at bottom of panel
    drawCores(panelX + 10.0f, panelY + 58.0f, panelW - 20.0f);

    // FPS top-left
    drawFPS(10.0f, 10.0f);
}

void HUD::drawResources() {
    const Materials::Quantities mats = game.getPlayer().getBalance();
    // icon positions
    float x = (ctx.window.getSize().x - 260.0f) * 0.5f + 12.0f;
    float y = 16.0f;
    const float iconS = 20.0f;

    struct R { const char* file; unsigned int value; const char* name; };
    R resources[3] = {
        { "icon_gold.png", mats.au, "Au" },
        { "icon_silver.png", mats.ag, "Ag" },
        { "icon_copper.png", mats.cu, "Cu" }
    };

    for (int i = 0; i < 3; ++i) {
        const auto& tex = ctx.renderer.getTexture(std::string(resources[i].file));
        sf::Sprite spr(tex);
        auto sz = tex.getSize();
        spr.setScale({iconS / float(sz.x), iconS / float(sz.y)});
        spr.setPosition({x + i * 80.0f, y});
        ctx.window.draw(spr);

        // value
        sf::Text t(font, std::to_string(resources[i].value), 16);
        t.setFillColor(sf::Color::White);
        t.setPosition({x + i * 80.0f + 26.0f, y - 2.0f});
        ctx.window.draw(t);
    }
}

void HUD::drawCores(float x, float y, float width) {
    Cores cores = game.getCores();
    int safe = cores.getSafe();
    int stolen = cores.getStolen();
    int lost = cores.getLost();
    int total = safe + stolen + lost;
    if (total == 0) return;

    const float spacing = 4.0f;
    const int maxPerRow = 12;
    const float rectHeight = 10.0f;
    float rectWidth = (width - (maxPerRow - 1) * spacing) / maxPerRow;
    float totalWidth = maxPerRow * (rectWidth + spacing) - spacing;
    float startX = x + (width - totalWidth) * 0.5f;
    
    float curX = startX, curY = y;
    int i = 0;

    // Draw cores
    for (int idx = 0; idx < total; ++idx) {
        if (i >= maxPerRow) { 
            i = 0;
            curY += rectHeight + spacing;
            curX = startX;
        }
        
        sf::RectangleShape rect({rectWidth, rectHeight});
        rect.setPosition({curX, curY});

        if (idx < safe) rect.setFillColor(sf::Color(0,150,255));  // Blue for safe
        else if (idx < safe + stolen) rect.setFillColor(sf::Color(255,140,0));  // Orange for stolen
        else rect.setFillColor(sf::Color(200,50,50));  // Red for lost

        ctx.window.draw(rect);
        curX += rectWidth + spacing;
        ++i;
    }
}

void HUD::drawFPS(float x, float y) {
    sf::Text t(font, "FPS: " + std::to_string((int) lastFPS), 14);
    t.setFillColor(sf::Color::White);
    t.setPosition({x, y});
    ctx.window.draw(t);
}
