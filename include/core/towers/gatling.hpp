#ifndef GATLING_HPP
#define GATLING_HPP

#include "core/towers/tower.hpp"

namespace tdg::core {

    class Gatling final : public Tower {
    public:
        explicit Gatling(int x, int y) noexcept;
        ~Gatling() override = default;

        void update(float dt, FrameEvents events, const std::vector<CreaturePtr>& creatures) override;
    };

} // namespace tdg::core

#endif // GATLING_HPP