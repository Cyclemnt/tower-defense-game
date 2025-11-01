#include <iostream>
#include <iomanip>
#include <sstream>
#include "../../include/gui/hud.hpp"
#include "../../include/renderer/renderer.hpp"
#include "../../include/resources/materials.hpp"

HUD::HUD(const RenderContext& ctx_, const Game& game_)
    : ctx(ctx_), game(game_)
{
    if (!font.openFromFile("../assets/gui/Lexend-Black.ttf")) {
        std::cerr << "[HUD] Failed to load font ../assets/Lexend-Black.ttf\n";
    }
}

void HUD::draw(float deltaTime) {
    // Refresh FPS every second
    if (fpsClock.getElapsedTime().asSeconds() > 1.0f) {
        if (deltaTime > 1e-6f) lastFPS = 1.0f / deltaTime;
        fpsClock.restart();
    }

    const sf::Vector2u win = ctx.window.getSize();
    const float scale = static_cast<float>(win.x) / 1920.0f; // base scale from 1080p reference

    drawResourcesPanel();
    drawWavePanel(scale);
    drawFPSPanel(scale);
    if (game.isOver()) drawGameOver();
    if (game.victory()) drawVictory();
}

void HUD::drawResourcesPanel() const {
    const sf::Vector2u win = ctx.window.getSize();
    const float scale = static_cast<float>(win.x) / 1920.0f;

    const float panelW = 260.0f * scale;
    const float panelH = 92.0f * scale;
    const float panelX = (win.x - panelW) * 0.5f;
    const float panelY = 8.0f * scale;

    sf::RectangleShape panel({panelW, panelH});
    panel.setPosition({panelX, panelY});
    panel.setFillColor(sf::Color(0, 0, 0, 150));
    panel.setOutlineThickness(2.0f * scale);
    panel.setOutlineColor(sf::Color(80, 80, 80));
    ctx.window.draw(panel);

    // Draw resources
    const Materials::Quantities mats = *game.getView()->playerBalance;
    const float iconSize = 20.0f * scale;
    const float spacing = 80.0f * scale;
    const float baseX = panelX + 12.0f * scale;
    const float baseY = panelY + 16.0f * scale;

    struct Icon { const char* file; unsigned int value; };
    const Icon resources[3] = {
        {"icon_gold.png", mats.au},
        {"icon_silver.png", mats.ag},
        {"icon_copper.png", mats.cu}
    };

    for (int i = 0; i < 3; ++i) {
        const sf::Texture& tex = ctx.renderer.getTexture(resources[i].file);
        sf::Sprite icon(tex);
        const sf::Vector2u sz = tex.getSize();
        icon.setScale({iconSize / sz.x, iconSize / sz.y});
        icon.setPosition({baseX + i * spacing, baseY});
        ctx.window.draw(icon);

        sf::Text valueTxt(font, std::to_string(resources[i].value), static_cast<unsigned int>(16 * scale));
        valueTxt.setFillColor(sf::Color::White);
        valueTxt.setPosition({baseX + i * spacing + 26.0f * scale, baseY - 2.0f * scale});
        ctx.window.draw(valueTxt);
    }

    // Draw cores below
    drawCores({panelX + 10.0f * scale, panelY + 58.0f * scale}, panelW - 20.0f * scale, scale);
}

void HUD::drawCores(sf::Vector2f position, float width, float scale) const {
    const Cores cores = *game.getView()->cores;
    const unsigned safe = cores.getSafe();
    const unsigned stolen = cores.getStolen();
    const unsigned lost = cores.getLost();
    const unsigned total = safe + stolen + lost;
    if (total == 0) return;

    const float spacing = 4.0f * scale;
    const int maxPerRow = 12;
    const float rectHeight = 10.0f * scale;
    const float rectWidth = (width - (maxPerRow - 1) * spacing) / maxPerRow;
    const float totalWidth = maxPerRow * (rectWidth + spacing) - spacing;
    const float startX = position.x + (width - totalWidth) * 0.5f;

    float curX = startX, curY = position.y;
    int i = 0;

    for (unsigned idx = 0; idx < total; ++idx) {
        if (i >= maxPerRow) {
            i = 0;
            curY += rectHeight + spacing;
            curX = startX;
        }

        sf::RectangleShape rect({rectWidth, rectHeight});
        rect.setPosition({curX, curY});

        if (idx < safe) rect.setFillColor(sf::Color(0, 150, 255));
        else if (idx < safe + stolen) rect.setFillColor(sf::Color(255, 140, 0));
        else rect.setFillColor(sf::Color(200, 50, 50));

        ctx.window.draw(rect);
        curX += rectWidth + spacing;
        ++i;
    }
}

void HUD::drawWavePanel(float scale) const {
    const sf::Vector2u win = ctx.window.getSize();
    const float panelW = 200.0f * scale;
    const float panelH = 70.0f * scale;
    const float panelX = 10.0f * scale;
    const float panelY = 8.0f * scale;

    sf::RectangleShape panel({panelW, panelH});
    panel.setPosition({panelX, panelY});
    panel.setFillColor(sf::Color(0, 0, 0, 150));
    panel.setOutlineThickness(2.0f * scale);
    panel.setOutlineColor(sf::Color(80, 80, 80));
    ctx.window.draw(panel);

    // --- Text info ---
    const std::unique_ptr<const Game::View> view = game.getView();
    const int currentWave = view->currentWave;
    const int totalWaves = view->totalWaves;
    const int timeToNext = view->timeBeforeNext;

    sf::Text waveTxt(font, "Wave " + std::to_string(currentWave) + " / " + std::to_string(totalWaves),
                     static_cast<unsigned int>(16 * scale));
    waveTxt.setFillColor(sf::Color::White);
    waveTxt.setPosition({panelX + 10.0f * scale, panelY + 10.0f * scale});
    ctx.window.draw(waveTxt);

    std::ostringstream ss;
    if (timeToNext > 0)
        ss << "Next in " << timeToNext << "s";
    else
        ss << "Wave active";

    sf::Text timerTxt(font, ss.str(), static_cast<unsigned int>(14 * scale));
    timerTxt.setFillColor(sf::Color(200, 200, 200));
    timerTxt.setPosition({panelX + 10.0f * scale, panelY + 36.0f * scale});
    ctx.window.draw(timerTxt);
}

void HUD::drawFPSPanel(float scale) const {
    const sf::Vector2u win = ctx.window.getSize();
    const float panelW = 100.0f * scale;
    const float panelH = 40.0f * scale;
    const float panelX = win.x - panelW - 10.0f * scale;
    const float panelY = 8.0f * scale;

    sf::RectangleShape panel({panelW, panelH});
    panel.setPosition({panelX, panelY});
    panel.setFillColor(sf::Color(0, 0, 0, 150));
    panel.setOutlineThickness(2.0f * scale);
    panel.setOutlineColor(sf::Color(80, 80, 80));
    ctx.window.draw(panel);

    sf::Text txt(font, "FPS: " + std::to_string(static_cast<int>(lastFPS)),
                 static_cast<unsigned int>(16 * scale));
    txt.setFillColor(sf::Color::White);
    txt.setPosition({panelX + 10.0f * scale, panelY + 8.0f * scale});
    ctx.window.draw(txt);
}

void HUD::drawGameOver() const {
    const sf::Vector2u winSize = ctx.window.getSize();
    const float width = static_cast<float>(winSize.x);
    const float height = static_cast<float>(winSize.y);

    // Dim the screen slightly
    sf::RectangleShape overlay({width, height});
    overlay.setFillColor(sf::Color(0, 0, 0, 180)); // dark semi-transparent overlay
    ctx.window.draw(overlay);

    // GAME OVER text
    const float scale = width / 1920.0f; // scale relative to base HD resolution
    sf::Text text(font, "GAME OVER", static_cast<unsigned int>(128 * scale));
    text.setFillColor(sf::Color(255, 60, 60));
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(6.0f * scale);

    // center text
    const sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.position.x + bounds.size.x * 0.5f,
                    bounds.position.y + bounds.size.y * 0.5f});
    text.setPosition({width * 0.5f, height * 0.5f});

    ctx.window.draw(text);
}

void HUD::drawVictory() const {
    const sf::Vector2u winSize = ctx.window.getSize();
    const float width = static_cast<float>(winSize.x);
    const float height = static_cast<float>(winSize.y);

    // Semi-transparent overlay
    sf::RectangleShape overlay({width, height});
    overlay.setFillColor(sf::Color(0, 0, 0, 180)); // dark background
    ctx.window.draw(overlay);

    // Text
    const float scale = width / 1920.0f;
    sf::Text text(font, "MISSION COMPLETE", static_cast<unsigned int>(96 * scale));
    text.setFillColor(sf::Color(50, 255, 100)); // bright green
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(6.0f * scale);

    // Center text
    const sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.position.x + bounds.size.x * 0.5f,
                    bounds.position.y + bounds.size.y * 0.5f});
    text.setPosition({width * 0.5f, height * 0.5f});

    ctx.window.draw(text);

    // Subtext
    sf::Text subtext(font, "You defended all cores!", static_cast<unsigned int>(36 * scale));
    subtext.setFillColor(sf::Color::White);
    subtext.setOutlineColor(sf::Color::Black);
    subtext.setOutlineThickness(3.0f * scale);
    const sf::FloatRect subBounds = subtext.getLocalBounds();
    subtext.setOrigin({subBounds.position.x + subBounds.size.x * 0.5f, subBounds.position.y});
    subtext.setPosition({width * 0.5f, height * 0.5f + 90.0f * scale});
    ctx.window.draw(subtext);
}
