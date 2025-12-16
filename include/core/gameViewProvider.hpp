#ifndef HUD_PROVIDER_HPP
#define HUD_PROVIDER_HPP

#include <functional>
#include <optional>
#include "core/player.hpp"

namespace tdg::core {

    struct GameView {
        Materials materials{};
        unsigned int coresSafe{};
        unsigned int coresStolen{};
        unsigned int coresLost{};

        unsigned int currentWave{};
        unsigned int totalWaves{};
        float timeToNextWave{};
    };

    using GameViewProvider = std::function<std::optional<GameView>()>;

}

#endif // HUD_PROVIDER_HPP