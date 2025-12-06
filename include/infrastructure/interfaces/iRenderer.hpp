#ifndef I_RENDERER_HPP
#define I_RENDERER_HPP

#include <vector>
#include "core/map.hpp"

namespace tdg::core { class Creature; class Tower; }

    namespace tdg::infra {

    class IRenderer {
    public:
        virtual ~IRenderer() = default;

        virtual void beginFrame() = 0;
        virtual void drawMap(const core::Map&) = 0;
        virtual void drawCreatures(const std::vector<core::Creature*>&) = 0;
        virtual void drawTowers(const std::vector<core::Tower*>&) = 0;
        virtual void endFrame() = 0;
    };

} // namespace tdg::infra

#endif // I_RENDERER_HPP