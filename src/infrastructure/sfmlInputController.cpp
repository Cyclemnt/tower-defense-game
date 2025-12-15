// #include <cmath>
// #include <cassert>
// #include "infrastructure/sfmlInputController.hpp"

// namespace tdg::infra {
    
//     SFMLInputController::SFMLInputController(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<float> tileSize)
//         : m_window(window), m_tileSize(tileSize)
//     {
//         m_tileOverlay.setSize(sf::Vector2f(*m_tileSize, *m_tileSize));
//         m_tileOverlay.setFillColor(sf::Color(255,255,255,60)); // default translucent
//         m_tileOverlay.setOutlineThickness(1.0f);
//         m_tileOverlay.setOutlineColor(sf::Color(255,255,255,120));

//         m_rangeOverlay.setFillColor(sf::Color(255,255,255,30));
//         m_rangeOverlay.setOutlineThickness(1.0f);
//     }

//     std::pair<int,int> SFMLInputController::pixelToTile(int pixelX, int pixelY) const {
//         assert(m_window);
//         sf::Vector2i pixel = sf::Vector2i(pixelX, pixelY);
//         sf::Vector2f world = m_window->mapPixelToCoords(pixel);
//         int tx = static_cast<int>(std::floor(world.x / *m_tileSize));
//         int ty = static_cast<int>(std::floor(world.y / *m_tileSize));
//         return {tx, ty};
//     }

//     void SFMLInputController::handleMouseMove(int pixelX, int pixelY) {
//         auto [tx, ty] = pixelToTile(pixelX, pixelY);
//         if (tx == m_lastTx && ty == m_lastTy) return; // no change

//         sf::Vector2i pixel = sf::Vector2i(pixelX, pixelY);
//         sf::Vector2f world = m_window->mapPixelToCoords(pixel);
//         updateHoverTile(tx, ty, world);
//     }

//     void SFMLInputController::handleMouseClick(int pixelX, int pixelY, sf::Mouse::Button button) {
//         auto [tx, ty] = pixelToTile(pixelX, pixelY);
//         // Right click cancels build/selection
//         if (button == sf::Mouse::Button::Right) {
//             cancelMode();
//             return;
//         }

//         switch (m_mode) {
//             case InputMode::Build: if (m_buildType.has_value()) break; // build tower m_buildType at tx ty
//             case InputMode::Sell: break; // sell tower at tx ty
//             case InputMode::Upgrade: break; // upgrade tower at tx ty
//             case InputMode::Normal: break; // could notify GUI to show tower panel / or show informations about the tower
//             default: break;
//         }
//     }

//     void SFMLInputController::handleKey(sf::Keyboard::Key key, bool pressed) {
//         if (!pressed) return;
//         if (key == sf::Keyboard::Key::Escape) {
//             // toggle pause - GameManager owns pause state; how to call it?
//         } else if (key == sf::Keyboard::Key::R) {
//             // convenience: restart level, GameManager owns that method too
//         }
//     }

//     void SFMLInputController::renderOverlay(sf::RenderTarget& target) {
//         if (m_lastTx < 0 || m_lastTy < 0) return;
//         // Convert tile indices to world coordinates
//         sf::FloatRect rect(sf::Vector2f(m_lastTx * *m_tileSize, m_lastTy * *m_tileSize), sf::Vector2f(*m_tileSize, *m_tileSize));
//         m_tileOverlay.setPosition(rect.position);
//         target.draw(m_tileOverlay);

//         m_rangeOverlay.setPosition(rect.position + rect.size * 0.5f);
//         target.draw(m_rangeOverlay);
//     }

//     // WRONG. A CERTAIN BUILD MODE SHOULD ONLY BE ALLOWED IF THE PLAYER CAN AFFORD IT.
//     void SFMLInputController::setBuildMode(std::string& towerType) { m_mode = InputMode::Build; m_buildType = towerType; }
//     void SFMLInputController::setSellMode() { m_mode = InputMode::Sell; m_buildType.reset(); }
//     void SFMLInputController::setUpgradeMode() { m_mode = InputMode::Upgrade; m_buildType.reset(); }
//     void SFMLInputController::cancelMode() { m_mode = InputMode::Normal; m_buildType.reset(); clearHover(); }

//     void SFMLInputController::updateHoverTile(int tx, int ty, const sf::Vector2f& worldPos) {
//         m_lastTx = tx; m_lastTy = ty;

//         // Default overlay color
//         sf::Color fill(255,255,255,60);
//         sf::Color outline(255,255,255,120);

//         if (m_mode == InputMode::Build && m_buildType.has_value()) {
//             bool buildable;
//             bool canAfford;
//             if (buildable && canAfford) {
//                 fill = sf::Color(100,220,100,100); // greenish
//                 outline = sf::Color(50,180,50,200);
//             } else {
//                 fill = sf::Color(220,100,100,100); // reddish
//                 outline = sf::Color(200,50,50,200);
//             }
//         } else if (m_mode == InputMode::Sell) {
//             if (/*tx ty has tower*/) {
//                 fill = sf::Color(255,180,80,120); // orange
//                 outline = sf::Color(200,120,50,200);
//             } else {
//                 fill = sf::Color(200,80,80,80);
//             }
//         } else {
//             // Normal hover: light gray
//             fill = sf::Color(200,200,200,50);
//             outline = sf::Color(220,220,220,120);

//             // Si tx ty a une tour, on affiche un cercle qui montre la range de la tour. Uniquement en mode normal, et quand on survole une tile occupée par une tour.
//         }

//         m_tileOverlay.setFillColor(fill);
//         m_tileOverlay.setOutlineColor(outline);
//     }

//     void SFMLInputController::clearHover() {
//         m_lastTx = m_lastTy = -1;
//     }

//     // Comment on gère le zoom avec la molette et le pan avec click and drag ?
//     // Il faut changer m_window->getView();

// } // namespace tdg::infra
