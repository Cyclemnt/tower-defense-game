// #ifndef SFML_INPUT_CONTROLLER_HPP
// #define SFML_INPUT_CONTROLLER_HPP

// #include <SFML/Graphics.hpp>
// #include <functional>
// #include <optional>
// #include <memory>

// namespace tdg::engine { class Game; };
// namespace tdg::core { class IVideoRenderer; class Tower; };

// namespace tdg::infra {

//     enum class InputMode { Normal, Build, Sell, Upgrade };
    
//     class SFMLInputController final {
//     public:
//         SFMLInputController(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<float> tileSize);

//         void handleEvent(const sf::Event& event);

//         // Event handlers called by GameManager
//         void handleMouseMove(int pixelX, int pixelY);
//         void handleMouseClick(int pixelX, int pixelY, sf::Mouse::Button button);
//         void handleKey(sf::Keyboard::Key key, bool pressed);

//         // Called from render phase of the game loop, after world is drawn but before GUI
//         void renderOverlay(sf::RenderTarget& target);

//         // Mode switches
//         void setBuildMode(std::string& towerType);
//         void setSellMode();
//         void setUpgradeMode();
//         void cancelMode();

//         // Callbacks
//         std::function<void(int tx,int ty,const std::string& towerType)> onBuildRequest;
//         std::function<void(int tx,int ty)> onSellRequest;
//         std::function<void(int tx,int ty)> onUpgradeRequest;
//         std::function<void()> onCancelMode;

//     private:
//         std::shared_ptr<sf::RenderWindow> m_window{nullptr};
//         std::shared_ptr<float> m_tileSize{nullptr};

//         InputMode m_mode{InputMode::Normal};
//         std::optional<std::string&> m_buildType;

//         // last hovered tile
//         int m_lastTx{-1}, m_lastTy{-1};

//         // overlay shapes
//         sf::RectangleShape m_tileOverlay;
//         sf::CircleShape m_rangeOverlay;

//         // helpers
//         void updateHoverTile(int tx, int ty, const sf::Vector2f& worldPos);
//         void clearHover();
//         std::pair<int,int> pixelToTile(int pixelX, int pixelY) const;
//     };

// } // namespace tdg::infra

// #endif // SFML_INPUT_CONTROLLER_HPP
