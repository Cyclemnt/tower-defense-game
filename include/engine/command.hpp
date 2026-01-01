#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <variant>
#include <optional>
#include <SFML/System/Vector2.hpp>

namespace tdg::engine {

    struct BuildPayload { std::string towerType; int tx; int ty; };
    struct UpgradePayload { int tx; int ty; };
    struct SellPayload { int tx; int ty; };
    struct setGameSpeedPayload { float speed; };
    struct PanViewPayload { sf::Vector2i delta; };
    struct ZoomViewPayload { float factor; sf::Vector2i focus; };
    struct LeftClickPayload { sf::Vector2i pixel; };
    struct MouseMovedPayload { sf::Vector2i pixel; };

    struct Command {
        using Payload = std::variant<std::monostate,
                                    BuildPayload,
                                    UpgradePayload,
                                    SellPayload,
                                    setGameSpeedPayload,
                                    PanViewPayload,
                                    ZoomViewPayload,
                                    LeftClickPayload,
                                    MouseMovedPayload>;

        enum class Type {
            Build, Upgrade, Sell,
            TogglePause, setSpeed,
            ResetView, PanView, ZoomView,
            LeftClick, MouseMoved,
            RestartLevel, NextLevel, Quit,
            MainMenu, StartStory, StartArcade
        };

        Command::Type type;
        std::optional<Command::Payload> payload;
    };

} // namespace tdg::engine

#endif // COMMAND_HPP