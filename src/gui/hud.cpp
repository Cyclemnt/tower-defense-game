#include <iostream>
#include <array>
#include <cmath>
#include "../../include/gui/hud.hpp"
#include "../../include/renderer/renderer.hpp"

HUD::HUD() {
    if (!font.openFromFile("../assets/gui/arial.ttf")) {
        std::cerr << "[HUD] Could not load font ../assets/arial.ttf\n";
    }
}

void HUD::render(RenderContext& ctx, const Game& game, float deltaTime) {
    // Update FPS every 0.25s
    if (fpsClock.getElapsedTime().asSeconds() > 0.25f) {
        if (deltaTime > 1e-6f) lastFPS = 1.0f / deltaTime;
        fpsClock.restart();
    }

    // Draw a small HUD in top center
    sf::Vector2u win = ctx.window.getSize();
    float panelW = 260.0f;
    float panelH = 110.0f;
    float panelX = (win.x - panelW) * 0.5f;
    float panelY = 8.0f;

    // panel
    sf::RectangleShape panel({panelW, panelH});
    panel.setPosition({panelX, panelY});
    panel.setFillColor(sf::Color(0,0,0,150));
    panel.setOutlineThickness(2.0f);
    panel.setOutlineColor(sf::Color(80,80,80));
    ctx.window.draw(panel);

    drawResources(ctx, game);

    // cores area at bottom of panel
    drawCores(ctx, game, panelX + 10.0f, panelY + 58.0f, panelW - 20.0f);

    // FPS top-left
    drawFPS(ctx, 10.0f, 10.0f);
}

void HUD::drawResources(RenderContext& ctx, const Game& game) {
    auto mats = game.getPlayer().getMaterials().getBalance();
    // icon positions
    float x = (ctx.window.getSize().x - 260.0f) * 0.5f + 12.0f;
    float y = 16.0f;
    const float iconS = 20.0f;

    struct R { const char* file; int value; const char* name; };
    R resources[3] = {
        { "icon_gold.png", mats[0], "Au" },
        { "icon_silver.png", mats[1], "Ag" },
        { "icon_copper.png", mats[2], "Cu" }
    };

    for (int i=0;i<3;i++) {
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

void HUD::drawCores(RenderContext& ctx, const Game& game, float x, float y, float width) {
    Cores cores = game.getCores();
    int safe = cores.getSafe();
    int stolen = cores.getStolen();
    int lost = cores.getLost();
    int total = safe + stolen + lost;
    if (total == 0) return;

    const float radius = 6.0f;
    float spacing = 14.0f;
    float maxPerLine = std::floor(width / spacing);
    float curX = x;
    float curY = y;

    int i = 0;
    for (int idx = 0; idx < total; ++idx) {
        if (i >= (int)maxPerLine) { i = 0; curY += (radius*2 + 4.0f); curX = x; }
        sf::CircleShape c(radius);
        c.setPosition({curX, curY});
        c.setOutlineThickness(1.0f);
        c.setOutlineColor(sf::Color(200,200,200));
        if (idx < safe) c.setFillColor(sf::Color(0,150,255));
        else if (idx < safe + stolen) c.setFillColor(sf::Color(255,140,0));
        else c.setFillColor(sf::Color(200,50,50));
        ctx.window.draw(c);
        curX += spacing;
        ++i;
    }
}

void HUD::drawFPS(RenderContext& ctx, float x, float y) {
    sf::Text t(font, "FPS: " + std::to_string((int) lastFPS), 14);
    t.setFillColor(sf::Color::White);
    t.setPosition({x, y});
    ctx.window.draw(t);
}
