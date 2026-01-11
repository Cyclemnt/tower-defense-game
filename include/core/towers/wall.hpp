#ifndef WALL_HPP
#define WALL_HPP

#include "core/towers/tower.hpp"

namespace tdg::core {

    class Wall final : public Tower {
    public:
        explicit Wall(int x, int y, Materials cost) noexcept;
        ~Wall() override = default;

        void update(float dt, Events& events, const std::vector<CreaturePtr>& creatures) override; // Main function to update cooldown, select target and shoot

        bool upgrade() override; // Upgrades tower stats
        std::string spriteId() const noexcept override; // To get the a sting ID (used to draw)
        void draw(IVideoRenderer& vidRenderer) const override; // Draws the tower
    };

} // namespace tdg::core

#endif // WALL_HPP