#ifndef HUD_PROVIDER_HPP
#define HUD_PROVIDER_HPP

#include <functional>
#include <optional>
#include "core/player.hpp"

namespace tdg::core {

    struct HUDState {
        Materials materials{};
        unsigned int coresSafe{};
        unsigned int coresStolen{};
        unsigned int coresLost{};

        unsigned int currentWave{};
        unsigned int totalWaves{};
        float timeToNextWave{};
    };

    using HUDProvider = std::function<std::optional<HUDState>()>;

}

#endif // HUD_PROVIDER_HPP