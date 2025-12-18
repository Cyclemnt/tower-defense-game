#ifndef GATLING_HPP
#define GATLING_HPP

#include "core/towers/tower.hpp"

namespace tdg::core {

    class Gatling final : public Tower {
    public:
        explicit Gatling(int x, int y) noexcept;
        ~Gatling() override = default;

        void update(float dt, Events& events, const std::vector<CreaturePtr>& creatures) override; // Main function to update cooldown, select target and shoot

        bool upgrade() override; // Upgrades tower stats
        std::string spriteId() const noexcept override; // To get the a sting ID (used to draw)
    };

} // namespace tdg::core

#endif // GATLING_HPP