#include "../../include/gui/towerPanel.hpp"
#include "../../include/tiles/openZone.hpp"
#include "../../include/renderer/renderer.hpp"
#include <iostream>

TowerPanel::TowerPanel(const RenderContext& ctx_, Game& game_)
    : ctx(ctx_), game(game_)
{
    entries = { // Must create tower icons instead of printing one directly (ugly)
        {"Gatling", "tower_gatling_icon.png", {0u, 0u, 50u}, [](sf::Vector2i pos){ return std::make_unique<Gatling>(pos); }},
        {"Mortar",  "tower_mortar_icon.png",  {0u, 0u, 75u},  [](sf::Vector2i pos){ return std::make_unique<Mortar>(pos); }},
        {"Laser",   "tower_laser_icon.png",   {0u, 10u, 100u}, [](sf::Vector2i pos){ return std::make_unique<Laser>(pos); }}
    };

    if (!font.openFromFile("../assets/gui/Lexend-Black.ttf")) {
        std::cerr << "[TowerPanel] Failed to load font ../assets/gui/Lexend-Black.ttf\n";
    }

    texGold   = &ctx.renderer.getTexture("icon_gold.png");
    texSilver = &ctx.renderer.getTexture("icon_silver.png");
    texCopper = &ctx.renderer.getTexture("icon_copper.png");
}

sf::FloatRect TowerPanel::getPanelRect() const {
    const sf::Vector2u win = ctx.window.getSize();
    const float w = win.x * 0.18f;
    const float h = win.y * 0.22f;
    const float x = 10.0f;
    const float y = win.y - h - 10.0f;
    return {{x, y}, {w, h}};
}

void TowerPanel::updateAffordability() {
    const Materials::Quantities& bal = *game.getView()->playerBalance;
    bool oneAffordable = false;
    for (TowerPanel::TowerEntry& e : entries) {
        e.affordable = (bal.au >= e.cost.au && bal.ag >= e.cost.ag && bal.cu >= e.cost.cu);
        if (e.affordable) oneAffordable = true;
    }
    if (!oneAffordable && !sellingMode) selectedIndex = -1;
}

void TowerPanel::drawPanel(sf::RenderWindow& win) const {
    sf::FloatRect r = getPanelRect();
    sf::RectangleShape bg({r.size.x, r.size.y});
    bg.setPosition({r.position.x, r.position.y});
    bg.setFillColor(sf::Color(0, 0, 0, 160));
    bg.setOutlineThickness(2.0f);
    bg.setOutlineColor(sf::Color(60, 60, 60));
    win.draw(bg);
}

void TowerPanel::drawCostIcons(sf::RenderWindow& win, const TowerEntry& e, sf::Vector2f basePos, float scale) {
    const float iconSize = 20.0f * scale;
    const float spacing = 80.0f * scale;
    float x = basePos.x;

    struct Icon { const sf::Texture* tex; unsigned int value; };
    const Icon icons[3] = {
        {texGold, e.cost.au},
        {texSilver, e.cost.ag},
        {texCopper, e.cost.cu}
    };

    for (int i = 0; i < 3; ++i) {
        const Icon& ic = icons[i];
        if (!ic.tex || ic.value == 0) continue;

        const sf::Vector2u sz = ic.tex->getSize();
        sf::Sprite sprite(*ic.tex);
        sprite.setScale({iconSize / sz.x, iconSize / sz.y});
        sprite.setPosition({x, basePos.y});
        if (!e.affordable) sprite.setColor(sf::Color(150, 150, 150, 150));
        win.draw(sprite);

        sf::Text valueTxt(font, std::to_string(ic.value), static_cast<unsigned int>(16 * scale));
        valueTxt.setFillColor(e.affordable ? sf::Color::White : sf::Color(140, 140, 140));
        valueTxt.setPosition({x + 26.0f * scale, basePos.y - 2.0f * scale});
        win.draw(valueTxt);

        x += spacing;
    }
}

void TowerPanel::drawTowers(sf::RenderWindow& win) {
    sf::FloatRect panel = getPanelRect();
    const float scale = ctx.window.getSize().x / 1920.0f; // scale to resolution
    const float margin = 10.0f * scale;
    const float lineH = (panel.size.y - 40.0f * scale) / static_cast<float>(entries.size()) - margin * 0.5f;
    const float iconSize = lineH * 0.7f;

    updateAffordability();

    for (size_t i = 0; i < entries.size(); ++i) {
        TowerPanel::TowerEntry& e = entries[i];
        const float y = panel.position.y + margin + i * lineH;

        sf::RectangleShape rect({panel.size.x - 2 * margin, lineH - 5.0f * scale});
        rect.setPosition({panel.position.x + margin, y});
        e.rect = rect.getGlobalBounds();

        if (sellingMode) rect.setFillColor(sf::Color(150, 60, 60, 150));
        else if ((int)i == selectedIndex) rect.setFillColor(sf::Color(200, 180, 60, 160));
        else if (e.affordable) rect.setFillColor(sf::Color(80, 80, 80, 180));
        else rect.setFillColor(sf::Color(50, 50, 50, 100));

        rect.setOutlineThickness(1.5f * scale);
        rect.setOutlineColor(sf::Color(90, 90, 90));
        win.draw(rect);

        // Tower icon
        const sf::Texture& tex = ctx.renderer.getTexture(e.textureName);
        sf::Sprite icon(tex);
        const sf::Vector2u sz = tex.getSize();
        float scaleIcon = iconSize / static_cast<float>(std::max(sz.x, sz.y));
        icon.setScale({scaleIcon, scaleIcon});
        icon.setPosition({rect.getPosition().x + 6.0f * scale, rect.getPosition().y + (rect.getSize().y - iconSize) * 0.5f});
        if (!e.affordable) icon.setColor(sf::Color(150, 150, 150, 150));
        win.draw(icon);

        // Tower name
        sf::Text name(font, e.name, static_cast<unsigned int>(18.0f * scale));
        name.setPosition({rect.getPosition().x + iconSize + 16.0f * scale, rect.getPosition().y + 4.0f * scale});
        name.setFillColor(e.affordable ? sf::Color::White : sf::Color(140, 140, 140));
        win.draw(name);

        // Cost icons under the name
        drawCostIcons(win, e, {rect.getPosition().x + iconSize + 16.0f * scale, rect.getPosition().y + lineH * 0.45f}, scale);
    }
}

void TowerPanel::drawSellButton(sf::RenderWindow& win) {
    sf::FloatRect panel = getPanelRect();
    const float scale = ctx.window.getSize().x / 1920.0f;
    const float margin = 10.0f * scale;
    const float btnH = 28.0f * scale;
    const float y = panel.position.y + panel.size.y - btnH - margin;

    sf::RectangleShape rect({panel.size.x - 2 * margin, btnH});
    rect.setPosition({panel.position.x + margin, y});
    sellRect = rect.getGlobalBounds();

    rect.setFillColor(sellingMode ? sf::Color(200, 80, 80, 180) : sf::Color(120, 40, 40, 150));
    rect.setOutlineThickness(1.5f * scale);
    rect.setOutlineColor(sf::Color(90, 90, 90));
    win.draw(rect);

    sf::Text txt(font, "Sell Mode", static_cast<unsigned int>(16.0f * scale));
    txt.setPosition({rect.getPosition().x + 20.0f * scale, rect.getPosition().y + 3.0f * scale});
    txt.setFillColor(sf::Color::White);
    win.draw(txt);
}

void TowerPanel::draw() {
    sf::RenderWindow& win = ctx.window;
    drawPanel(win);
    drawTowers(win);
    drawSellButton(win);
}

bool TowerPanel::handleClick(const sf::Vector2i& mousePos) {
    // Sell button
    if (sellRect.contains({(float)mousePos.x, (float)mousePos.y})) {
        sellingMode = !sellingMode;
        selectedIndex = -1;
        sellingMode ? game.playerState = Player::State::Selling : game.playerState = Player::State::None;
        return true;
    }

    // Tower buttons
    for (size_t i = 0; i < entries.size(); ++i) {
        TowerPanel::TowerEntry& e = entries[i];
        if (e.rect.contains({(float)mousePos.x, (float)mousePos.y})) {
            if (!e.affordable) return true;
            sellingMode = false;
            selectedIndex = (selectedIndex == (int)i ? -1 : (int)i);
            selectedIndex == -1 ? game.playerState = Player::State::None : game.playerState = Player::State::Building;
            return true;
        }
    }
    
    return false;
}

void TowerPanel::handleTileClick(const sf::Vector2i& tilePos) {
    if (sellingMode) {
        game.trySellTower(tilePos);
        return;
    }

    if (selectedIndex >= 0 && selectedIndex < (int)entries.size()) {
        const TowerPanel::TowerEntry& e = entries[selectedIndex];
        std::unique_ptr<Tower> tower = e.factory(tilePos);
        game.tryPlaceTower(std::move(tower));
    }
}
