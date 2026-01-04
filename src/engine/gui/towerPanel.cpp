#include "engine/gui/towerPanel.hpp"

#include "engine/iGame.hpp"
#include "engine/commandBus.hpp"

#include "core/materials.hpp"

#include "core/interfaces/iVideoRenderer.hpp"

namespace tdg::engine {
    
    TowerPanel::TowerPanel(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<float> tileSize, std::shared_ptr<CommandBus> bus)
        : m_window(window), m_tileSize(tileSize), m_bus(bus)
    {
        m_towerNames = {"Gatling", "Mortar", "Laser"};
        m_towerPanels.push_back(sf::FloatRect());
        m_towerPanels.push_back(sf::FloatRect());
        m_towerPanels.push_back(sf::FloatRect());
    }
    
    void TowerPanel::draw(core::IVideoRenderer& vidRenderer) {
        drawBackPanel(vidRenderer);
        drawTowerButtons(vidRenderer);
        drawUpgradeBtn(vidRenderer);
        drawSellBtn(vidRenderer);
    }

    void TowerPanel::drawOverlays(core::IVideoRenderer& vidRenderer) {
        vidRenderer.drawRectangle(m_tileOverlay.getPosition().x, m_tileOverlay.getPosition().y, m_tileOverlay.getSize().x, m_tileOverlay.getSize().y, utils::Color(m_tileOverlay.getFillColor().r, m_tileOverlay.getFillColor().g, m_tileOverlay.getFillColor().b, m_tileOverlay.getFillColor().a));
        vidRenderer.drawCircle(m_towerRangeOverlay.getPosition().x + m_towerRangeOverlay.getRadius(), m_towerRangeOverlay.getPosition().y + m_towerRangeOverlay.getRadius(), m_towerRangeOverlay.getRadius(), utils::Color(0u,0u,0u,0u), m_towerRangeOverlay.getOutlineThickness(), utils::Color(m_towerRangeOverlay.getOutlineColor().r, m_towerRangeOverlay.getOutlineColor().g, m_towerRangeOverlay.getOutlineColor().b, m_towerRangeOverlay.getOutlineColor().a));
    }

    bool TowerPanel::handleClick(const sf::Vector2i& mousePos) {
        if (m_game.expired()) return false;

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
                bool affordable = m_game.lock()->canAfford(m_towerNames[i]);;
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
            Command c{Command::Type::Sell, SellPayload{tilePos.x, tilePos.y}};
            m_bus->push(std::move(c));
            return;
        }
        if (m_mode == Mode::Upgrade) {
            Command c{Command::Type::Upgrade, UpgradePayload{tilePos.x, tilePos.y}};
            m_bus->push(std::move(c));
            return;
        }
        else {
            Command c{Command::Type::Build, std::nullopt};
            switch (m_mode) {
                case Mode::Gatling: c.payload = BuildPayload{"Gatling", tilePos.x, tilePos.y}; break;
                case Mode::Mortar: c.payload = BuildPayload{"Mortar", tilePos.x, tilePos.y}; break;
                case Mode::Laser: c.payload = BuildPayload{"Laser", tilePos.x, tilePos.y}; break;
                default: break;
            }
            if (c.payload.has_value()) m_bus->push(std::move(c));
        }
    }

    void TowerPanel::handleMouseMove(const sf::Vector2i& tilePos) {
        if (m_game.expired()) return;

        if (m_game.lock()->tileOpenAt(tilePos.x, tilePos.y)) {
            m_tileOverlay = sf::RectangleShape({*m_tileSize, *m_tileSize});
            m_tileOverlay.setPosition({static_cast<float>(tilePos.x) * *m_tileSize, static_cast<float>(tilePos.y) * *m_tileSize});

            if (m_game.lock()->towerAt(tilePos.x, tilePos.y)) {
                switch (m_mode) {
                    case Mode::Sell: m_tileOverlay.setFillColor(sf::Color(255,50,50,80)); break;
                    case Mode::Upgrade: m_tileOverlay.setFillColor(sf::Color(255,160,50,80)); break;
                    case Mode::None: m_tileOverlay.setFillColor(sf::Color(50,50,50,80)); break;
                    default: m_tileOverlay.setFillColor(sf::Color(50,50,50,80)); break;
                }
                if (m_mode == Mode::None) {
                    float radius = m_game.lock()->towerRangeAt(tilePos.x, tilePos.y).value() * *m_tileSize;
                    m_towerRangeOverlay = sf::CircleShape(radius);
                    m_towerRangeOverlay.setPosition({(static_cast<float>(tilePos.x) + 0.5f) * *m_tileSize - radius, (static_cast<float>(tilePos.y) + 0.5f) * *m_tileSize - radius});
                    m_towerRangeOverlay.setFillColor(sf::Color(0, 0, 0, 0));
                    m_towerRangeOverlay.setOutlineThickness(5.0f);
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

    void TowerPanel::setGamePtr(std::weak_ptr<IGame> game) {
        m_game = game;
    }

    void TowerPanel::drawBackPanel(core::IVideoRenderer& vidRenderer) {
        float panelW = 356;
        float panelH = 302;
        float panelX = 10.0f;
        float panelY = m_window->getSize().y - panelH - 10.0f;
        m_backPanel = sf::FloatRect({panelX, panelY}, {panelW, panelH});

        vidRenderer.drawRectangle(panelX, panelY, panelW, panelH, {0u,0u,0u,160u}, 2.0f, {60u,60u,60u});
    }

    void TowerPanel::drawTowerButtons(core::IVideoRenderer& vidRenderer) {
        if (m_game.expired()) return;

        const float margin = 10.0f;
        const float lineH = (m_backPanel.size.y - 86.0f) / 3.0f - margin * 0.5f;
        const float iconSize = lineH * 0.7f;

        std::string towerIconNames[3] = {"icons/gatling", "icons/mortar", "icons/laser"};
        std::string matsIconNames[3] = {"icons/gold", "icons/silver", "icons/copper"};

        for (size_t i = 0; i < 3; ++i) {
            bool affordable = m_game.lock()->canAfford(m_towerNames[i]);

            const float btnW = m_backPanel.size.x - 2 * margin;
            const float btnH = lineH - 5.0f;
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

            const float thickness = 1.5f;

            vidRenderer.drawRectangle(btnX, btnY, btnW, btnH, fill, thickness, {90u,90u,90u});

            // Tower icon
            const float iconX = btnX + 6.0f;
            const float iconY = btnY + (btnH - iconSize) * 0.5f;

            utils::Color spriteColor = {255u,255u,255u,255u};
            if (!affordable) spriteColor.setColor(150u,150u,150u,150u);
            vidRenderer.drawSprite(towerIconNames[i], iconX, iconY, iconSize, spriteColor);

            // Tower name
            utils::Color text;
            if (m_game.lock()->canAfford(m_towerNames[i])) text = {255u,255u,255u,255u};
            else text = {140u,140u,140u,255u};
            vidRenderer.drawText(m_towerNames[i], 18.0f, btnX + iconSize + 16.0f, btnY + 4.0f, {255u,255u,255u});

            // Costs
            float costX = btnX + iconSize + 16.0f;
            float costY = btnY + lineH * 0.45f;
            const float costIconSize = 20.0f;
            const float spacing = 80.0f;

            std::optional<core::Materials> cost = m_game.lock()->towerCost(m_towerNames[i]);
            if (!cost.has_value()) return;

            std::vector<unsigned int> costButInAVector = {cost.value().au, cost.value().ag, cost.value().cu};

            for (int j = 0; j < 3; ++j) {
                utils::Color costIconColor = {255u,255u,255u,255u};
                if (!affordable) costIconColor.setColor(150u,150u,150u,150u);
                vidRenderer.drawSprite(matsIconNames[j], costX, costY, costIconSize, costIconColor);
                vidRenderer.drawText(std::to_string(costButInAVector[j]), 16, costX + 26.0f, costY - 2.0f, costIconColor);
                costX += spacing;
            }
        }
    }

    void TowerPanel::drawUpgradeBtn(core::IVideoRenderer& vidRenderer) {
        const float margin = 10.0f;
        const float btnW = m_backPanel.size.x - 2.0f * margin;
        const float btnH = 28.0f;
        const float btnX = m_backPanel.position.x + margin;
        const float btnY = m_backPanel.position.y + m_backPanel.size.y - 2.0f * btnH - 2.0f * margin;
        const float btnThickness = 1.5f;

        // "Hitbox"
        m_upgradeRect = sf::FloatRect({btnX, btnY}, {btnW, btnH});

        // Button
        utils::Color fill;
        if (m_mode == Mode::Upgrade) fill = {195u,200u,80u,180u};
        else fill = {115u,120u,40u,150u};
        vidRenderer.drawRectangle(btnX, btnY, btnW, btnH, fill, btnThickness, {90u,90u,90u,255u});

        // Text
        const float txtSize = 16.0f;
        const float txtX = btnX + 20.0f;
        const float txtY = btnY + 3.0f;
        vidRenderer.drawText("Upgrade Mode", txtSize, txtX, txtY, {255u,255u,255u,255u});
    }

    void TowerPanel::drawSellBtn(core::IVideoRenderer& vidRenderer) {
        const float margin = 10.0f;
        const float btnW = m_backPanel.size.x - 2.0f * margin;
        const float btnH = 28.0f;
        const float btnX = m_backPanel.position.x + margin;
        const float btnY = m_backPanel.position.y + m_backPanel.size.y - btnH - margin;
        const float btnThickness = 1.5f;

        // "Hitbox"
        m_sellRect = sf::FloatRect({btnX, btnY}, {btnW, btnH});

        // Button
        utils::Color fill;
        if (m_mode == Mode::Sell) fill = {200u,80u,80u,180u};
        else fill = {120u,40u,40u,150u};
        vidRenderer.drawRectangle(btnX, btnY, btnW, btnH, fill, btnThickness, {90u,90u,90u,255u});

        // Text
        const float txtSize = 16.0f;
        const float txtX = btnX + 20.0f;
        const float txtY = btnY + 3.0f;
        vidRenderer.drawText("Sell Mode", txtSize, txtX, txtY, {255u,255u,255u,255u});
    }

} // namespace tdg::engine
